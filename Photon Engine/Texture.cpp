#include "Texture.h"

#include "GLEW/glew.h"
#include "FreeImage/FreeImage.h"

#include "System.h"

namespace ph_engine {

	Texture::Texture() {
		target = GL_TEXTURE_2D;
	}

	void Texture::loadFromFile(const char* path) {
		this->path = path;
		GLubyte* image_data = nullptr;

		FREE_IMAGE_FORMAT img_type = FIF_UNKNOWN;
		FIBITMAP* bitmap(nullptr);

		img_type = FreeImage_GetFileType(path);
		if (img_type == FIF_UNKNOWN)
			img_type = FreeImage_GetFIFFromFilename(path);

		if (img_type == FIF_UNKNOWN) {
#ifdef _DEBUG
			std::cerr << "Error load image[Fail to recognize]: " << path << std::endl;
#endif
			return;
		}

		if (FreeImage_FIFSupportsReading(img_type))
			bitmap = FreeImage_Load(img_type, path);
		if (!bitmap) {
#ifdef _DEBUG
			std::cerr << "Error load image[Fail to load]: " << path << std::endl;
#endif
			return;
		}

		image_data = (GLubyte*)FreeImage_GetBits(bitmap);

		width = FreeImage_GetWidth(bitmap);
		heigth = FreeImage_GetHeight(bitmap);

		components = channelsCount(path);

		GLuint image_format = GL_RGB;
		if (components == TEXTURE_CHANNELS::GREY)
			image_format = GL_RED;
		else if (components == TEXTURE_CHANNELS::RGB)
			image_format = GL_RGB;
		else if (components == TEXTURE_CHANNELS::RGBA)
			image_format = GL_RGBA;

		glGenTextures(1, &objectID);
		bind();
		glTexImage2D(target, 0, image_format, width, heigth, 0, GL_BGRA, GL_UNSIGNED_BYTE, image_data);
		glGenerateMipmap(target);

		FreeImage_Unload(bitmap);
	}
	void Texture::emptyTexture(TEXTURE_TYPE textureType, uint width, uint height){
		this->heigth = height;
		this->width = width;
		this->type = textureType;

		glGenTextures(1, &objectID);
		bind();
		switch (textureType) {
			case TEXTURE_TYPE::COLOR:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
				break;
			case TEXTURE_TYPE::DEPTH:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
				break;
			case TEXTURE_TYPE::STENCIL:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX, width, height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL);
				break;
		}
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	void Texture::save(const char* path){
		GLubyte* pixels = new GLubyte[width*heigth * 3];
		GLenum format = GL_BGR;
		int pitch = width;
		switch (type){
			case TEXTURE_TYPE::COLOR:
				format = GL_BGR;
				pitch *= 3;
				break;
			case TEXTURE_TYPE::DEPTH:
				format = GL_DEPTH_COMPONENT;
				break;
			case TEXTURE_TYPE::STENCIL:
				format = GL_STENCIL_INDEX;
				break;
		}

		bind();
		glReadPixels(0, 0, width, heigth, format, GL_UNSIGNED_BYTE, pixels);

		FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, heigth, pitch,
			24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		FreeImage_Save(FIF_PNG, image, path);
		FreeImage_Unload(image);

		delete[] pixels;
	}

	void Texture::activeTexture(uint num) {
		if (num >= 0 && num <= 31) {
			glActiveTexture(GL_TEXTURE0 + num);
		}
	}

	void Texture::bind() {
		glBindTexture(target, objectID);
	}
	uint Texture::getID(){
		return objectID;
	}

	Texture::TEXTURE_CHANNELS Texture::channelsCount(const char* path){
		uint channels = 1;
		bool red = false, green = false, blue = false;

		FREE_IMAGE_FORMAT img_type = FIF_UNKNOWN;
		FIBITMAP* bitmap(nullptr);

		img_type = FreeImage_GetFileType(path);
		if (img_type == FIF_UNKNOWN)
			img_type = FreeImage_GetFIFFromFilename(path);

		if (FreeImage_FIFSupportsReading(img_type))
			bitmap = FreeImage_Load(img_type, path);

		if (FreeImage_GetChannel(bitmap, FREE_IMAGE_COLOR_CHANNEL::FICC_RED))
			red = true;
		if (FreeImage_GetChannel(bitmap, FREE_IMAGE_COLOR_CHANNEL::FICC_GREEN))
			green = true;
		if (FreeImage_GetChannel(bitmap, FREE_IMAGE_COLOR_CHANNEL::FICC_BLUE))
			blue = true;

		if (red && green && blue) {
			channels = 3;

			if (FreeImage_GetChannel(bitmap, FREE_IMAGE_COLOR_CHANNEL::FICC_ALPHA))
				return TEXTURE_CHANNELS::RGBA;
			else
				return TEXTURE_CHANNELS::RGB;
		}

		return TEXTURE_CHANNELS::GREY;
	}
}

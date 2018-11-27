#include "Texture.h"

#include "GLEW/glew.h"
#include "FreeImage/FreeImage.h"

#include "System.h"

namespace ph_engine {

	Texture::Texture() {
		target = GL_TEXTURE_2D;
		glGenTextures(1, &objectID);
	}

	// Load texture from file
	void Texture::loadFromFile(const char* path) {
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

		GLuint image_format;
		if (components == Texture::GREY)
			image_format = GL_RED;
		else if (components == Texture::RGB)
			image_format = GL_RGB;
		else if (components == Texture::RGBA)
			image_format = GL_RGBA;

		bind();
			glTexImage2D(target, 0, image_format, width, heigth, 0, GL_BGRA, GL_UNSIGNED_BYTE, image_data);
			glGenerateMipmap(target);
		unbind();

		FreeImage_Unload(bitmap);
	}

	void Texture::emptyTexture(TEXTURE_TYPE textureType, uint width, uint height){
		this->heigth = height;
		this->width = width;

		switch (textureType) {
			case Texture::COLOR:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
				break;
			case Texture::DEPTH:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
				break;
			case Texture::STENCIL:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX, width, height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL);
				break;
		}
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Texture::activeTexture(uint num) {
		if (num >= 0 && num <= 31) {
			glActiveTexture(GL_TEXTURE0 + num);
		}
	}

	void Texture::bind() {
		glBindTexture(target, objectID);
	}
	void Texture::unbind() {
		glBindTexture(target, 0);
	}
	uint Texture::getID(){
		return objectID;
	}

	Texture::TEXTURE_CHANNELS Texture::channelsCount(const char* path){
		uint channels = 0;
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

		if (red || green || blue)
			channels = 1;

		if (red && green && blue) {
			channels = 3;

			if (FreeImage_GetChannel(bitmap, FREE_IMAGE_COLOR_CHANNEL::FICC_ALPHA))
				return Texture::RGBA;
		}

		if (channels == 1) return Texture::GREY;
		if (channels == 3) return Texture::RGB;
	}
}

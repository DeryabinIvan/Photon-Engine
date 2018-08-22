#include "Texture.h"

#include "GLEW/glew.h"
#include "SOIL/SOIL.h"

namespace ph_engine {

	Texture::Texture() {
		target = GL_TEXTURE_2D;
	}

	// Load texture from file
	void Texture::loadFromFile(const char* path, TEXTURE_LOAD_TYPE type) {
		GLubyte* image = SOIL_load_image(path, &width, &heigth, 0, type == RGB ? SOIL_LOAD_RGB : SOIL_LOAD_RGBA);

		GLuint image_target = (type == RGB ? GL_RGB : GL_RGBA);
		glGenTextures(1, &objectID);
		bind();
		//Filtering settings

		glTexImage2D(target, 0, image_target, width, heigth, 0, image_target, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(target);
		SOIL_free_image_data(image);
		unbind();
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
}

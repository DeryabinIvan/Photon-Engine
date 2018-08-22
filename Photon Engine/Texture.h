#pragma once

#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	enum TEXTURE_LOAD_TYPE { RGB, RGBA };

	class PHOTONENGINE_API Texture:public GLObject {
		int width, heigth;

		public:
		Texture();
		// Load texture from file
		void loadFromFile(const char* path, TEXTURE_LOAD_TYPE type = RGB);

		void activeTexture(uint);

		// Inherited via GLObject
		void bind();
		void unbind();
	};
}

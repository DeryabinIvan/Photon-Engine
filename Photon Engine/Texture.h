#pragma once

#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	enum TEXTURE_LOAD_TYPE { RGB, RGBA };
	enum TEXTURE_TYPE {DIFFUSE=1, SPECULAR, DEFAULT};

	class PHOTONENGINE_API Texture:public GLObject {
		int width, heigth;
		TEXTURE_TYPE type;

		public:
		Texture();
		// Load texture from file
		void loadFromFile(const char* path, TEXTURE_LOAD_TYPE type = RGB);
		void loadFromFile(const char* path, TEXTURE_TYPE type = DEFAULT);

		static void activeTexture(uint);
		TEXTURE_TYPE getType() { return type; }

		// Inherited via GLObject
		void bind();
		void unbind();
	};
}

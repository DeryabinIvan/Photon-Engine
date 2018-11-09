#pragma once

#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	class PHOTONENGINE_API Texture:public GLObject {
		public:
			enum TEXTURE_LOAD_TYPE { RGB, RGBA };
			enum TEXTURE_TYPE { DIFFUSE = 1, SPECULAR, DEFAULT };

			Texture();
			// Load texture from file
			void loadFromFile(const char* path, TEXTURE_LOAD_TYPE type = RGB);
			void loadFromFile(const char* path, TEXTURE_TYPE type = DEFAULT);

			static void activeTexture(uint);
			TEXTURE_TYPE getType() { return type; }

			void bind();
			static void bind(uint id);
			void unbind();

		private:
			int width, heigth;
			TEXTURE_TYPE type;
	};
}

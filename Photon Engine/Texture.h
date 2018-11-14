#pragma once

#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	class PHOTONENGINE_API Texture:public GLObject {
		public:
			enum TEXTURE_LOAD_TYPE { RGB, RGBA };
			enum TEXTURE_TYPE { COLOR, DEPTH, STENCIL };

			Texture();
			// Load texture from file
			void loadFromFile(const char* path, TEXTURE_LOAD_TYPE type = RGB);
			// Create empty texture
			void emptyTexture(TEXTURE_TYPE textureType, uint width, uint height);

			static void activeTexture(uint);
			TEXTURE_TYPE getType() { return type; }

			void bind();
			void unbind();
			uint getID();

		private:
			int width, heigth;
			TEXTURE_TYPE type;
	};
}

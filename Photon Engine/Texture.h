#pragma once

#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	class PHOTONENGINE_API Texture:public GLObject {
		public:
			enum TEXTURE_TYPE { COLOR, DEPTH, STENCIL };
			enum TEXTURE_CHANNELS { GREY = 1, RGB = 3, RGBA = 4 };

			Texture();
			// Load texture from file
			void loadFromFile(const char* path);
			// Create empty texture
			void emptyTexture(TEXTURE_TYPE textureType, uint width, uint height);

			static void activeTexture(uint);
			TEXTURE_TYPE getType() { return type; }

			void bind();
			void unbind();
			uint getID();

		private:
			int width, heigth, components;
			TEXTURE_TYPE type;

			TEXTURE_CHANNELS channelsCount(const char* path);
	};
}

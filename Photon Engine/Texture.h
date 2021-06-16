#pragma once

#include "Config.h"
#include "GLObject.h"
#include <string>

namespace ph_engine {
	class PHOTONENGINE_API Texture:public GLObject {
		public:
			enum class TEXTURE_TYPE { COLOR, DEPTH, STENCIL };
			enum class TEXTURE_CHANNELS { GREY = 1, RGB = 3, RGBA = 4 };

			Texture();

			// Load texture from file
			void loadFromFile(const char* path);

			// Create empty texture
			void emptyTexture(TEXTURE_TYPE textureType, uint width, uint height);

			//Save texture to file
			void save(const char* path);

			static void activeTexture(uint);
			TEXTURE_TYPE getType() { return type; }

			void bind();
			uint getID();

		private:
		    int width, heigth;
			std::string path;
			
			TEXTURE_CHANNELS components;
			TEXTURE_TYPE type = TEXTURE_TYPE::COLOR;

			TEXTURE_CHANNELS channelsCount(const char* path);
	};
}

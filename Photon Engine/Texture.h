#pragma once

#include "Config.h"
#include "GLObject.h"
#include <string>

namespace ph_engine {
	class PHOTONENGINE_API Texture:public GLObject {
		public:
			enum class TEXTURE_COLOR_TYPE { COLOR, DEPTH, STENCIL };
			enum class TEXTURE_TYPE { DIFFUSE, SPECULAR, NORMAL, AMBIENT_OCCLUSION, ROUGNESS };
			enum class TEXTURE_CHANNELS { GREY = 1, RGB = 3, RGBA = 4 };

			Texture();

			// Load texture from file
			void loadFromFile(const char* path);

			// Create empty texture
			void emptyTexture(TEXTURE_COLOR_TYPE textureType, int width, int height);

			//Save texture to file
			void save(const char* path);

			static void activeTexture(int);
			TEXTURE_COLOR_TYPE getType() { return type; }

			void bind();
			int getID();

		private:
		    int width, heigth;
			std::string path;
			
			TEXTURE_CHANNELS components;
			TEXTURE_COLOR_TYPE type = TEXTURE_COLOR_TYPE::COLOR;

			TEXTURE_CHANNELS channelsCount(const char* path);
	};
}

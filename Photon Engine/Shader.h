#pragma once

#include "GLObject.h"
#include "GL_Enums.h"

namespace ph_engine {
	class PHOTONENGINE_API Shader:GLObject {
		public:
		bool loadFromStr(const char* str, SHADER_TYPE type);
		bool loadFromFile(const char* filename, SHADER_TYPE type);

		GLuint getID() { return objectID; }

		void remove();
	};
}
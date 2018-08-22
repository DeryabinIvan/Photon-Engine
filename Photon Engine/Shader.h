#pragma once

#include "Config.h"

#include "GLObject.h"
#include "GL_Enums.h"

namespace ph_engine {
	class PHOTONENGINE_API Shader:GLObject {
		public:
		bool loadFromStr(const char* str, SHADER_TYPE type);
		bool loadFromFile(const char* filename, SHADER_TYPE type);

		uint getID() { return objectID; }

		void remove();
	};
}
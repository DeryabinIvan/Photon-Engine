#pragma once

#include "GLObject.h"
#include "GL_Enums.h"

namespace ph_engine {
	class PHOTONENGINE_API EBO:GLObject {
		public:
		EBO();

		void load(size_t size, const void* data, DRAW_TYPE type = STATIC);

		// Inherited via GLObject
		void bind();
		void unbind();
	};
}

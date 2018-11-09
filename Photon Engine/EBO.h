#pragma once

#include "Config.h"
#include "GLObject.h"
#include "VBO.h"

namespace ph_engine {
	class PHOTONENGINE_API EBO:GLObject {
		public:
			EBO();

			void load(size_t size, const void* data, VBO::DRAW_TYPE type = VBO::STATIC);

			// Inherited via GLObject
			void bind();
			void unbind();
	};
}

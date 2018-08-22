#pragma once

#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	//VAO save VBO sates
	class PHOTONENGINE_API VAO:public GLObject {
		public:
		VAO();
		~VAO();

		void remove() {
			this->~VAO();
		}

		// Inherited via GLObject
		void bind();
		void unbind();
	};
}

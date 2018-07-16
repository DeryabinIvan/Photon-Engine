#pragma once

#include "GLObject.h"

namespace ph_engine {
	//VAO save VBO sates
	class PHOTONENGINE_API VAO:public GLObject {
		public:
		VAO();
		~VAO() {
			glDeleteBuffers(1, &objectID);
		}

		void remove() {
			this->~VAO();
		}

		// Inherited via GLObject
		void bind();
		void unbind();
	};
}

#include "stdafx.h"
#include "EBO.h"

namespace ph_engine {
	EBO::EBO() {
		target = GL_ELEMENT_ARRAY_BUFFER;
		glGenBuffers(1, &objectID);
	}

	void EBO::bind() {
		glBindBuffer(target, objectID);
	}
	void EBO::unbind() {
		glBindBuffer(target, 0);
	}
}

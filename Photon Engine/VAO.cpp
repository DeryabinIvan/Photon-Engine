#include "stdafx.h"
#include "VAO.h"

namespace ph_engine {
	VAO::VAO() {
		target = GL_ARRAY_BUFFER;

		glGenVertexArrays(1, &objectID);
	}

	void VAO::bind() {
		glBindVertexArray(objectID);
	}
	void VAO::unbind() {
		glBindVertexArray(0);
	}
}

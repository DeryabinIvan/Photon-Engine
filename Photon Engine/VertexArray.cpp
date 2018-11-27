#include "VertexArray.h"

#include "GLEW/glew.h"

namespace ph_engine {
	VertexArray::VertexArray() {
		target = GL_ARRAY_BUFFER;

		glGenVertexArrays(1, &objectID);
	}
	VertexArray::~VertexArray() {
		glDeleteBuffers(1, &objectID);
	}

	void VertexArray::bind() {
		glBindVertexArray(objectID);
	}
	void VertexArray::unbind() {
		glBindVertexArray(0);
	}
}

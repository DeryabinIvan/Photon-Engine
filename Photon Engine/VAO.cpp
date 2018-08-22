#include "VAO.h"

#include "GLEW/glew.h"

namespace ph_engine {
	VAO::VAO() {
		target = GL_ARRAY_BUFFER;

		glGenVertexArrays(1, &objectID);
	}
	VAO::~VAO() {
		glDeleteBuffers(1, &objectID);
	}

	void VAO::bind() {
		glBindVertexArray(objectID);
	}
	void VAO::unbind() {
		glBindVertexArray(0);
	}
}

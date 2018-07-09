#include "stdafx.h"
#include "VBO.h"

namespace ph_engine {
	VBO::VBO() {
		target = GL_ARRAY_BUFFER;

		glGenBuffers(1, &objectID);
	}

	void VBO::addVertexAttrib(GLuint index, GLuint size, GLboolean normalized, GLsizei stride, const GLvoid* offset) {
		glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride * sizeof(GLfloat), offset);
	}


	void VBO::bind() {
		glBindBuffer(target, objectID);
	}

	void VBO::unbind() {
		glBindBuffer(target, 0);
	}
}
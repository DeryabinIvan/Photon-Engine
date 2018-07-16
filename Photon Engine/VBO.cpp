#include "stdafx.h"
#include "VBO.h"

namespace ph_engine {
	VBO::VBO() {
		target = GL_ARRAY_BUFFER;

		glGenBuffers(1, &objectID);
	}

	void VBO::load(size_t size, const void * data, DRAW_TYPE type) {
		switch (type) {
			case STATIC:
			glBufferData(target, size, data, GL_STATIC_DRAW);
			break;
			case DYNAMIC:
			glBufferData(target, size, data, GL_DYNAMIC_DRAW);
			break;
			case STREAM:
			glBufferData(target, size, data, GL_STREAM_DRAW);
			break;
		}
	}

	void VBO::addVertexAttrib(GLuint index, GLuint size, GLboolean normalized, GLsizei stride, const GLvoid* offset) {
		glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride, offset);
	}


	void VBO::bind() {
		glBindBuffer(target, objectID);
	}

	void VBO::unbind() {
		glBindBuffer(target, 0);
	}
}
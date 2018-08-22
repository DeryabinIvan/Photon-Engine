#include "VBO.h"

#include "GLEW/glew.h"

namespace ph_engine {
	VBO::VBO() {
		target = GL_ARRAY_BUFFER;

		glGenBuffers(1, &objectID);
	}
	VBO::~VBO() {
		glDeleteVertexArrays(1, &objectID);
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

	void VBO::addVertexAttrib(uint index, uint size, bool normalized, int stride, const void* offset) {
		glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride, offset);
	}

	void VBO::enableAttrib(uint index) { glEnableVertexAttribArray(index); }
	void VBO::disableAttrib(uint index) { glDisableVertexAttribArray(index); }

	void VBO::bind() {
		glBindBuffer(target, objectID);
	}

	void VBO::unbind() {
		glBindBuffer(target, 0);
	}
}
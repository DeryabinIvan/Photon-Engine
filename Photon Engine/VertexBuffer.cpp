#include "VertexBuffer.h"

#include "GLEW/glew.h"

namespace ph_engine {
	VertexBuffer::VertexBuffer() {
		target = GL_ARRAY_BUFFER;

		glGenBuffers(1, &objectID);
	}
	VertexBuffer::~VertexBuffer() {
		glDeleteVertexArrays(1, &objectID);
	}

	void VertexBuffer::load(size_t size, const void * data, DRAW_TYPE type) {
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

	void VertexBuffer::addVertexAttrib(int index, int size, bool normalized, int stride, const void* offset) {
		glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride, offset);
	}

	void VertexBuffer::enableAttrib(int index) { glEnableVertexAttribArray(index); }
	void VertexBuffer::disableAttrib(int index) { glDisableVertexAttribArray(index); }

	void VertexBuffer::bind() {
		glBindBuffer(target, objectID);
	}

	void VertexBuffer::unbind() {
		glBindBuffer(target, 0);
	}
}
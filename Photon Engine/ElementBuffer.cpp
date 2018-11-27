#include "ElementBuffer.h"

#include "GLEW/glew.h"

namespace ph_engine {
	ElementBuffer::ElementBuffer() {
		target = GL_ELEMENT_ARRAY_BUFFER;
		glGenBuffers(1, &objectID);
	}

	void ElementBuffer::load(size_t size, const void * data, VertexBuffer::DRAW_TYPE type) {
		switch (type) {
			case VertexBuffer::STATIC:
				glBufferData(target, size, data, GL_STATIC_DRAW);
				break;
			case VertexBuffer::DYNAMIC:
				glBufferData(target, size, data, GL_DYNAMIC_DRAW);
				break;
			case VertexBuffer::STREAM:
				glBufferData(target, size, data, GL_STREAM_DRAW);
				break;
		}
	}

	void ElementBuffer::bind() {
		glBindBuffer(target, objectID);
	}
	void ElementBuffer::unbind() {
		glBindBuffer(target, 0);
	}
}

#include "stdafx.h"
#include "EBO.h"

namespace ph_engine {
	EBO::EBO() {
		target = GL_ELEMENT_ARRAY_BUFFER;
		glGenBuffers(1, &objectID);
	}

	void EBO::load(size_t size, const void * data, DRAW_TYPE type) {
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

	void EBO::bind() {
		glBindBuffer(target, objectID);
	}
	void EBO::unbind() {
		glBindBuffer(target, 0);
	}
}

#include "RenderBuffer.h"

#include "GLEW/glew.h"

namespace ph_engine {
	RenderBuffer::RenderBuffer(){
		target = GL_RENDERBUFFER;
		glGenRenderbuffers(1, &objectID);
	}
	RenderBuffer::~RenderBuffer(){
		remove();
	}

	void RenderBuffer::create(uint storComponet, uint width, uint height){
		glRenderbufferStorage(target, storComponet, width, height);
	}

	uint RenderBuffer::getID(){
		return objectID;
	}

	void RenderBuffer::bind(){
		glBindRenderbuffer(target, objectID);
	}
	void RenderBuffer::bindBaseBuffer(){
		glBindRenderbuffer(target, 0);
	}
	void RenderBuffer::remove(){
		glDeleteRenderbuffers(1, &objectID);
	}
}
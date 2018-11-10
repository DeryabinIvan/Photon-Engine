#include "RenderBuffer.h"

#include "GLEW/glew.h"

namespace ph_engine {
	RenderBuffer::RenderBuffer(){
		target = GL_RENDERBUFFER;
		glGenRenderbuffers(1, &objectID);
		if(!glIsRenderbuffer(objectID))
			std::cerr << "Created object isn`t RBO\n";
	}
	RenderBuffer::~RenderBuffer(){
		remove();
	}

	void RenderBuffer::create(uint width, uint height){
		glRenderbufferStorage(target, GL_DEPTH24_STENCIL8, width, height);
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
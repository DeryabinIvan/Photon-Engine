#include "FrameBuffer.h"

#include "GLEW/glew.h"

#include "System.h"

namespace ph_engine {
	FrameBuffer::FrameBuffer(){
		target = GL_FRAMEBUFFER;
		glGenFramebuffers(1, &objectID);
	}
	FrameBuffer::~FrameBuffer(){
		remove();
	}

	void FrameBuffer::attachTexture(Texture& texture, AttachmentType type){
		texture.bind();

		switch (type) {
			case AttachmentType::COLOR:
				glFramebufferTexture(target, GL_COLOR_ATTACHMENT0 , texture.getID(), 0);
				break;
			case AttachmentType::DEPTH:
				glFramebufferTexture(target, GL_DEPTH_ATTACHMENT, texture.getID(), 0);
				break;
			case AttachmentType::STENCIL:
				glFramebufferTexture(target, GL_STENCIL_ATTACHMENT, texture.getID(), 0);
				break;
		}
	}

	void FrameBuffer::attachRenderBuffer(RenderBuffer rb, int attachType){
		glFramebufferRenderbuffer(target, attachType, GL_RENDERBUFFER, rb.getID());
	}

	bool FrameBuffer::checkErrors(){
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE;
	}

	void FrameBuffer::bind(){
		glBindFramebuffer(target, objectID);
	}
	void FrameBuffer::bindBaseBuffer(){
		glBindFramebuffer(target, 0);
	}

	void FrameBuffer::colorBuffer(int buffer){
		glDrawBuffer(buffer);
	}

	void FrameBuffer::remove(){
		glDeleteFramebuffers(1, &objectID);
	}
}

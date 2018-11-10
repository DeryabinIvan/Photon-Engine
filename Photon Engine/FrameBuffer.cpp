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

	void FrameBuffer::attachTexture(uint width, uint height, AttachmentType type, uint blockNum){
		glGenTextures(1, &attachedTex);
		glBindTexture(GL_TEXTURE_2D, attachedTex);

		switch (type){
			case FrameBuffer::COLOR:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
				break;
			case FrameBuffer::DEPTH:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
				break;
			case FrameBuffer::STENCIL:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX, width, height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL);
				break;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		switch (type){
			case FrameBuffer::COLOR:
				glFramebufferTexture2D(target, GL_COLOR_ATTACHMENT0 + blockNum, GL_TEXTURE_2D, attachedTex, 0);
				break;
			case FrameBuffer::DEPTH:
				glFramebufferTexture2D(target, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, attachedTex, 0);
				break;
			case FrameBuffer::STENCIL:
				glFramebufferTexture2D(target, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, attachedTex, 0);
				break;
		}
	}

	void FrameBuffer::attachRenderBuffer(RenderBuffer rb, uint attachType){
		glFramebufferRenderbuffer(target, attachType, GL_RENDERBUFFER, rb.getID());
	}

	bool FrameBuffer::checkErrors(){
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE;
	}

	void FrameBuffer::bind(){
		glBindFramebuffer(target, objectID);
	}
	void FrameBuffer::bindTexture(){
		glBindTexture(GL_TEXTURE_2D, attachedTex);
	}
	void FrameBuffer::bindBaseBuffer(){
		glBindFramebuffer(target, 0);
	}

	void FrameBuffer::remove(){
		glDeleteFramebuffers(1, &objectID);
	}
}

#pragma once
#include "Config.h"
#include "GLObject.h"

#include "RenderBuffer.h"

namespace ph_engine {
	class PHOTONENGINE_API FrameBuffer:GLObject {
		uint attachedTex;

		public:
			enum AttachmentType {COLOR, DEPTH, STENCIL};

			FrameBuffer();
			~FrameBuffer();

			void attachTexture(uint width, uint height, AttachmentType type, uint blockNum = 0);
			void attachRenderBuffer(RenderBuffer rb);

			//@return return true if framebuffer not complete
			bool checkErrors();

			void bind();
			void bindTexture();
			void bindBaseBuffer();

			void remove();
	};
}

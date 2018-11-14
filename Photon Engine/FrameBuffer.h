#pragma once
#include "Config.h"
#include "GLObject.h"

#include "RenderBuffer.h"
#include "Texture.h"

namespace ph_engine {
	class PHOTONENGINE_API FrameBuffer:GLObject {
		public:
			enum AttachmentType {COLOR, DEPTH, STENCIL};

			FrameBuffer();
			~FrameBuffer();

			void attachTexture(Texture texture, AttachmentType type);
			void attachRenderBuffer(RenderBuffer rb, uint attachType);

			//@return return true if framebuffer not complete
			bool checkErrors();

			void bind();
			void bindBaseBuffer();
			void colorBuffer(uint buffer);

			void remove();
	};
}

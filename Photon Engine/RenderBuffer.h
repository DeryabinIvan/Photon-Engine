#pragma once
#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	class PHOTONENGINE_API RenderBuffer:GLObject{
		public:
			RenderBuffer();
			~RenderBuffer();

			void create(uint width, uint height);

			uint getID();

			void bind();
			void bindBaseBuffer();
			void remove();
	};
}

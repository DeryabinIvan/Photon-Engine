#pragma once
#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	class PHOTONENGINE_API RenderBuffer:GLObject{
		public:
			RenderBuffer();
			~RenderBuffer();

			void create(int storComponet, int width, int height);

			int getID();

			void bind();
			void bindBaseBuffer();
			void remove();
	};
}

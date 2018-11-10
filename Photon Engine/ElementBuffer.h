#pragma once

#include "Config.h"
#include "GLObject.h"
#include "VertexBuffer.h"

namespace ph_engine {
	class PHOTONENGINE_API ElementBuffer:GLObject {
		public:
			ElementBuffer();

			void load(size_t size, const void* data, VertexBuffer::DRAW_TYPE type = VertexBuffer::STATIC);

			// Inherited via GLObject
			void bind();
			void unbind();
	};
}

#pragma once

#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	class PHOTONENGINE_API VertexBuffer:GLObject {
		public:
			enum DRAW_TYPE { STATIC, DYNAMIC, STREAM };

			VertexBuffer();
			~VertexBuffer();

			void load(size_t size, const void* data, DRAW_TYPE type = STATIC);

			void remove() { this->~VertexBuffer(); }

			void addVertexAttrib(int index, int size, bool normalized, int stride, const void* offset = (void*) 0);
			//Enable attrib by index
			void enableAttrib(int index);
			//Disable attrib by index
			void disableAttrib(int index);

			void bind();
			void unbind();
	};
}
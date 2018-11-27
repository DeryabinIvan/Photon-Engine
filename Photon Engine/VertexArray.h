#pragma once

#include "Config.h"
#include "GLObject.h"

namespace ph_engine {
	//VertexArray save VertexBuffer sates
	class PHOTONENGINE_API VertexArray:GLObject {
		public:
			VertexArray();
			~VertexArray();

			void remove() {
				this->~VertexArray();
			}

			// Inherited via GLObject
			void bind();
			void unbind();
	};
}

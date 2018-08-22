#pragma once

#include "Config.h"
#include "GLObject.h"
#include "GL_Enums.h"

namespace ph_engine {
	class PHOTONENGINE_API VBO:GLObject {
		public:
		VBO();
		~VBO();

		void load(size_t size, const void* data, DRAW_TYPE type = STATIC);

		void remove() { this->~VBO(); }

		//@param stribe is automaticle mul by sizeof(float)
		void addVertexAttrib(uint index, uint size, bool normalized, int stride, const void* offset = (void*) 0);
		//Enable attrib by index
		void enableAttrib(uint index);
		//Disable attrib by index
		void disableAttrib(uint index);

		void bind();
		void unbind();
	};
}
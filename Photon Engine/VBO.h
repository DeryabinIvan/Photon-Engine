#pragma once

#include "GLObject.h"
#include "GL_Enums.h"

namespace ph_engine {
	class PHOTONENGINE_API VBO:GLObject {
		public:
		VBO();
		~VBO() { glDeleteVertexArrays(1, &objectID); }

		void load(size_t size, const void* data, DRAW_TYPE type = STATIC);

		void remove() { glDeleteVertexArrays(1, &objectID); }

		//@param stribe is automaticle mul by sizeof(float)
		void addVertexAttrib(GLuint index, GLuint size, GLboolean normalized, GLsizei stride, const GLvoid* offset = (GLvoid*) 0);
		//Enable attrib by index
		void enableAttrib(GLuint index) { glEnableVertexAttribArray(index); }
		//Disable attrib by index
		void disableAttrib(GLuint index) { glDisableVertexAttribArray(index); }

		void bind();
		void unbind();
	};
}
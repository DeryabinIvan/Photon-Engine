#pragma once

#include "GLObject.h"
#include "GL_Enums.h"

namespace ph_engine {
	class PHOTONENGINE_API VBO:GLObject {
		public:
		VBO();
		~VBO() { glDeleteVertexArrays(1, &objectID); }

		template<size_t N> void loadVert(GLfloat(&vert)[N], DRAW_TYPE type = STATIC);

		void remove() { glDeleteVertexArrays(1, &objectID); }

		//@param stribe is automaticle mul by sizeof(float)
		void addVertexAttrib(GLuint index, GLuint size, GLboolean normalized, GLsizei stride, const GLvoid* offset = (GLvoid*) 0);
		//Enable attrib by index
		void enableAttrib(GLuint index) { glEnableVertexAttribArray(index); }
		//Disable attrib by index
		void disableAttrib(GLuint index) { glDisableVertexAttribArray(index); }

		virtual void bind() override;
		virtual void unbind() override;
	};

	template<size_t N>
	inline void VBO::loadVert(GLfloat(&vert)[N], DRAW_TYPE type) {
		switch (type) {
			case STATIC:
			glBufferData(target, sizeof(vert), vert, GL_STATIC_DRAW);
			break;
			case DYNAMIC:
			glBufferData(target, sizeof(vert), vert, GL_DYNAMIC_DRAW);
			break;
			case STREAM:
			glBufferData(target, sizeof(vert), vert, GL_STREAM_DRAW);
			break;
		}

		/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);*/
	}
}
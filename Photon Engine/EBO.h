#pragma once

#include "GLObject.h"
#include "GL_Enums.h"

namespace ph_engine {
	class PHOTONENGINE_API EBO:GLObject {
		public:
		EBO();
		template<size_t N> void load(GLuint(&ind)[N], DRAW_TYPE type = STATIC);

		// Inherited via GLObject
		virtual void bind() override;
		virtual void unbind() override;
	};

	template<size_t N>
	inline void EBO::load(GLuint(&ind)[N], DRAW_TYPE type) {
		switch (type) {
			case STATIC:
			glBufferData(target, sizeof(ind), ind, GL_STATIC_DRAW);
			break;
			case DYNAMIC:
			glBufferData(target, sizeof(ind), ind, GL_DYNAMIC_DRAW);
			break;
			case STREAM:
			glBufferData(target, sizeof(ind), ind, GL_STREAM_DRAW);
			break;
		}
	}
}

#pragma once

#include "stdafx.h"

namespace ph_engine {
	class GLObject {
		protected:
		GLuint objectID, target = 0;

		public:
		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}

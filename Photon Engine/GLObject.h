#pragma once

#include "Config.h"
#include "GLEW/glew.h"

namespace ph_engine {
	class GLObject {
		protected:
			GLuint objectID = 0, target = 0;
	};
}

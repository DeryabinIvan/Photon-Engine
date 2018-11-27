#pragma once

#include "Config.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

namespace ph_engine {
	class PHOTONENGINE_API System {
		public:
			//Time
			static double getTime();
			static void setTime(double time);

			//Error
			static uint getGLError();
			static void printGLError();

			//OpenGL debug callback
			static void APIENTRY defualtDebugCallback(GLenum source, GLenum type, GLuint id,
				GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
			static void activeDebugOutput();
			static void setDebugCallback(GLDEBUGPROC debugCallback);
	};
}

#include "System.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

namespace ph_engine {
	double System::getTime() {
		return glfwGetTime();
	}
	void System::setTime(double time) {
		glfwSetTime(time);
	}

	uint System::getGLError(){
		return glGetError();
	}
	void System::printGLError(){
#ifdef _DEBUG
		uint error = getGLError();
		if (error != GL_NO_ERROR) {
			std::cerr << "OpenGL error: ";
			switch (error) {
				case GL_INVALID_ENUM:
					std::cerr << "GL_INVALID_ENUM" << std::endl;
					break;
				case GL_INVALID_VALUE:
					std::cerr << "GL_INVALID_VALUE" << std::endl;
					break;
				case GL_INVALID_OPERATION:
					std::cerr << "GL_INVALID_OPERATION" << std::endl;
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
					break;
				case GL_OUT_OF_MEMORY:
					std::cerr << "GL_OUT_OF_MEMORY" << std::endl;
					break;
				case GL_STACK_UNDERFLOW:
					std::cerr << "GL_STACK_UNDERFLOW" << std::endl;
					break;
				case GL_STACK_OVERFLOW:
					std::cerr << "GL_STACK_OVERFLOW" << std::endl;
					break;
			}
		}
#endif
	}

	void GLAPIENTRY System::defualtDebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
#ifdef _DEBUG
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
#endif
	}
	void System::activeDebugOutput(){
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(defualtDebugCallback, 0);
	}
	void System::setDebugCallback(GLDEBUGPROC debugCallback){
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(debugCallback, 0);
	}
}



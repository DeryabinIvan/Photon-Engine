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
	}
}



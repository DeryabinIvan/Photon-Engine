#include "System.h"

#include "GLFW/glfw3.h"

namespace ph_engine {
	double System::getTime() {
		return glfwGetTime();
	}

	void System::setTime(double time) {
		glfwSetTime(time);
	}
}



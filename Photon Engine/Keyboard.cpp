#include "stdafx.h"
#include "Keyboard.h"

namespace ph_engine {
	bool Keyboard::keys[GLFW_KEY_LAST];
	bool Keyboard::mode[3];

	void Keyboard::callback(GLFWwindow* window, int key, int scancode, int action, int _mode) {
		if (action == GLFW_PRESS) keys[key] = true;
		else if (action == GLFW_RELEASE) keys[key] = false;

		switch (_mode) {
			case GLFW_MOD_CONTROL:
			mode[0] = true;
			break;

			case GLFW_MOD_SHIFT:
			mode[1] = true;
			break;

			case GLFW_MOD_ALT:
			mode[2] = true;
			break;

			default:
			mode[0] = mode[1] = mode[2] = false;
		}
	}

	Keyboard::Keyboard(Window& window) {
		glfwSetKeyCallback(window.getGLFWPointer(), callback);
	}

	bool Keyboard::keyPressed(int key) const {
		return keys[key];
	}

	int Keyboard::getPressedKey() const {
		for (int i = 30; i < GLFW_KEY_LAST; i++)
			if (keys[i]) return i;
	}

	int Keyboard::keyMode() const {
		int result = 0;
		if (mode[0]) result |= GLFW_MOD_CONTROL;
		if (mode[1]) result |= GLFW_MOD_SHIFT;
		if (mode[2]) result |= GLFW_MOD_ALT;

		return result;
	}
}

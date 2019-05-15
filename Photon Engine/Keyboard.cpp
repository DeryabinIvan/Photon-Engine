#include "Keyboard.h"

#include <algorithm>

namespace ph_engine {
	bool Keyboard::mode[3];
	std::vector<int> Keyboard::p_keys;

	void Keyboard::callback(GLFWwindow* window, int key, int scancode, int action, int _mode) {
		if (action == GLFW_PRESS) {
			p_keys.push_back(key);
		}else if (action == GLFW_RELEASE) {
			p_keys.erase(std::remove(p_keys.begin(), p_keys.end(), key), p_keys.end());
		}

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
		if (!p_keys.empty())
			return std::find(p_keys.begin(), p_keys.end(), key) != p_keys.end();
		else
			return false;
	}

	bool Keyboard::keyPressedOnce(int key) const {
		if (!p_keys.empty()) {
			if (std::find(p_keys.begin(), p_keys.end(), key) != p_keys.end()) {
				p_keys.erase(std::remove(p_keys.begin(), p_keys.end(), key), p_keys.end());
				return true;
			}
		}
		return false;
	}

	int Keyboard::getPressedKey() const {
		if (!p_keys.empty())
			return p_keys.front();
		else
			return Keyboard::UNKNOWN;
	}

	std::vector<int> Keyboard::pressedKeys(){
		return p_keys;
	}

	int Keyboard::keyMode() const {
		int result = 0;
		if (mode[0]) result |= GLFW_MOD_CONTROL;
		if (mode[1]) result |= GLFW_MOD_SHIFT;
		if (mode[2]) result |= GLFW_MOD_ALT;

		return result;
	}
}

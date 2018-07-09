#include "stdafx.h"
#include "Mouse.h"

namespace ph_engine {
	bool Mouse::btn[GLFW_MOUSE_BUTTON_LAST];
	double Mouse::x = 0, Mouse::y = 0;
	double Mouse::scroll_x = 0, Mouse::scroll_y = 0;

	void Mouse::pos_callback(GLFWwindow* window, double xpos, double ypos) {
		x = xpos;
		y = ypos;
	}
	void Mouse::btn_callback(GLFWwindow* window, int _btn, int action, int mode) {
		if (action == GLFW_PRESS) btn[_btn] = true;
		else btn[_btn] = false;
	}
	void Mouse::scr_callback(GLFWwindow* window, double sx, double sy) {
		scroll_x = sx;
		scroll_y = sy;
	}

	Mouse::Mouse(GLFWwindow* _window) {
		window = _window;

		glfwSetCursorPosCallback(_window, pos_callback);
		glfwSetMouseButtonCallback(_window, btn_callback);
		glfwSetScrollCallback(_window, scr_callback);
	}

	void Mouse::setPosition(double x, double y) {
		glfwSetCursorPos(window, x, y);
	}

	void Mouse::setSensitivity(double sens) {
		this->sens = sens;
	}

	double Mouse::getSensitivity() const {
		return sens;
	}

	double Mouse::getX() const {
		return x;
	}
	double Mouse::getY() const {
		return y;
	}

	double Mouse::getScrollX() const {
		return scroll_x;
	}
	double Mouse::getScrollY() const {
		return scroll_y;
	}

	bool Mouse::pressed(int _btn) {
		return btn[_btn];
	}
}

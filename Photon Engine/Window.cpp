#include "stdafx.h"
#include "Window.h"

int ph_engine::Window::WINDOWS_COUNT = 0;

void ph_engine::Window::resize(GLFWwindow * id, int w, int h) {
	glViewport(0, 0, w, h);
}

ph_engine::Window::Window(int w, int h, const char* title) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	id = glfwCreateWindow(w, h, title, nullptr, nullptr);
	width = w;
	heigth = h;

	glViewport(0, 0, w, h);

	WINDOWS_COUNT++;
	if (WINDOWS_COUNT == 1) {
		setActive();

		glewExperimental = true;
		glewInit();
	}
}

ph_engine::Window::~Window() {
	WINDOWS_COUNT--;
	glfwDestroyWindow(id);
}

void ph_engine::Window::setActive() {
	glfwMakeContextCurrent(id);
}
void ph_engine::Window::swapBuffer() {
	glfwSwapBuffers(id);
}

bool ph_engine::Window::shouldClose() {
	return glfwWindowShouldClose(id);
}
void ph_engine::Window::close() {
	glfwSetWindowShouldClose(id, true);
}

void ph_engine::Window::pollEvents() {
	glfwPollEvents();
}

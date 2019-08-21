#include "Window.h"

namespace ph_engine {
	int Window::WINDOWS_COUNT = 0;

	void Window::resize(GLFWwindow* id, int w, int h) {
		glViewport(0, 0, w, h);
	}

	Window::Window(int w, int h, const char* title) {
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

	Window::Window(int w, int h, const char* title, WindowSettings& s) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, s.OPENGL_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, s.OPENGL_MINOR);
		
		if (s.framerate) {
			glfwWindowHint(GLFW_REFRESH_RATE, s.framerate);
		}
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

	Window::~Window() {
		WINDOWS_COUNT--;
		glfwDestroyWindow(id);
	}

	void Window::setActive() {
		glfwMakeContextCurrent(id);
	}
	void Window::swapBuffer() {
		glfwSwapBuffers(id);
	}

	void Window::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1);
	}

	void Window::clearColor(Color clearColor){
		glm::vec4 tmp = clearColor.toVec4();
		glClearColor(tmp.r, tmp.g, tmp.b, tmp.a);
	}

	void Window::clearBuffers(uint buffersList){
		glClear(buffersList);
	}

	void Window::draw(Render_Mode mode, uint first, uint count) {
		glDrawArrays(mode, first, count);
	}

	void Window::enableFeature(uint glFeature) {
		glEnable(glFeature);
	}

	void Window::disableFeature(uint glFeature) {
		glDisable(glFeature);
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(id);
	}
	void Window::close() {
		glfwSetWindowShouldClose(id, true);
	}

	void Window::hideCursor() {
		glfwSetInputMode(id, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::showCursor() {
		glfwSetInputMode(id, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Window::pollEvents() {
		glfwPollEvents();
	}

	GLFWwindow * Window::getGLFWPointer() {
		return id;
	}
}

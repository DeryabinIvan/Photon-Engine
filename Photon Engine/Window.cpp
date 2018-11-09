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
	glEnable(GL_DEPTH_TEST);
}

ph_engine::Window::Window(int w, int h, const char* title, WindowSettings& s) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, s.OPENGL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, s.OPENGL_MINOR);
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
	glEnable(GL_DEPTH_TEST);
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

void ph_engine::Window::clear() {
	if (!custom) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1);
	} else custom();
}

void ph_engine::Window::draw(Render_Mode mode, uint first, uint count){
	glDrawArrays(mode, first, count);
}

void ph_engine::Window::enableFeature(uint glFeature){
	glEnable(glFeature);
}

void ph_engine::Window::disableFeature(uint glFeature){
	glDisable(glFeature);
}

bool ph_engine::Window::shouldClose() {
	return glfwWindowShouldClose(id);
}
void ph_engine::Window::close() {
	glfwSetWindowShouldClose(id, true);
}

void ph_engine::Window::hideCursor() {
	glfwSetInputMode(id, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void ph_engine::Window::showCursor() {
	glfwSetInputMode(id, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void ph_engine::Window::pollEvents() {
	glfwPollEvents();
}

GLFWwindow * ph_engine::Window::getGLFWPointer() {
	return id;
}

#pragma once

#include "Config.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

namespace ph_engine {
	struct WindowSettings {
		unsigned char OPENGL_MAJOR, OPENGL_MINOR;
	};

	typedef void(*ClearFunction)(void);
	typedef void(*InitFunction)(void);

	class PHOTONENGINE_API Window {
		GLFWwindow* id;
		int width, heigth;

		void resize(GLFWwindow*, int, int);
		ClearFunction custom = nullptr;

		static int WINDOWS_COUNT;

		public:
			Window(int w, int h, const char* title);
			Window(int w, int h, const char* title, WindowSettings& s);

			~Window();

			void setActive();
			void swapBuffer();
			void clear();

			bool shouldClose();
			void close();
			void hideCursor();
			void showCursor();

			void pollEvents();
			GLFWwindow* getGLFWPointer();
	};
}


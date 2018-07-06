#pragma once

#include "stdafx.h"

namespace ph_engine {
	class WindowSettings {

	};

	class PHOTONENGINE_API Window {
		GLFWwindow* id;
		int width, heigth;

		void resize(GLFWwindow*, int, int);

		static int WINDOWS_COUNT;

		public:
			Window(int w, int h, const char* title);
			Window(int w, int h, const char* title, WindowSettings& s);

			~Window();

			void setActive();
			void swapBuffer();

			bool shouldClose();
			void close();

			void pollEvents();
	};
}


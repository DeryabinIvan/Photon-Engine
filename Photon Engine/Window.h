#pragma once

#include "Config.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include "Color.h"

namespace ph_engine {
	class PHOTONENGINE_API Window {
		GLFWwindow* id;
		int width, heigth;

		void resize(GLFWwindow*, int, int);

		static int WINDOWS_COUNT;

		public:
			enum Render_Mode { TRIANGLES = GL_TRIANGLES, POINTS = GL_POINTS };
			struct WindowSettings {
				unsigned char OPENGL_MAJOR = 3, OPENGL_MINOR = 3,
					framerate = 0;
			};

			typedef void(*ClearFunction)(void);
			typedef void(*InitFunction)(void);

			Window(int w, int h, const char* title);
			Window(int w, int h, const char* title, WindowSettings& s);

			~Window();

			void setTitle(const std::string title);
			void setActive();
			void swapBuffer();

			//default clear funtion
			void clear();
			void clearColor(Color clearColor);
			void clearBuffers(uint buffersList);

			void draw(Render_Mode mode, uint first, uint count);
			void enableFeature(uint glFeature);
			void disableFeature(uint glFeature);

			bool shouldClose();
			void close();
			void hideCursor();
			void showCursor();

			void pollEvents();
			GLFWwindow* getGLFWPointer();
	};
}


#pragma once

#include "stdafx.h"

namespace ph_engine {
	class PHOTONENGINE_API Keyboard {
		static void callback(GLFWwindow*, int, int, int, int);

		static bool keys[];
		static bool mode[];

		public:
		Keyboard(GLFWwindow* window);

		bool keyPressed(int key) const;
		int keyMode() const;
	};
}

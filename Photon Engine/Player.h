#pragma once

#include "GLFW/glfw3.h"

#include "Camera.h"

#include "Keyboard.h"
#include "Mouse.h"

namespace ph_engine {
	class PHOTONENGINE_API Player: public Camera {
		float speed;

		double lx = 400, ly = 300;
		double yaw = -90, pitch = 0;

		public:
		Player(glm::vec3 posistion, float speed);
		Player(float x, float y, float z, float speed);

		void move(const Keyboard& key);
		void look(const Mouse& mouse);
	};
}


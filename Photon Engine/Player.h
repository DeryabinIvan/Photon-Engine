#pragma once
#pragma warning( disable:4244 )

#include "Camera.h"

#include "Keyboard.h"
#include "Mouse.h"

#include "GLFW/glfw3.h"

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


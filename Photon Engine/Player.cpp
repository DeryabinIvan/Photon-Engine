#include "stdafx.h"
#include "Player.h"

#pragma warning( disable:4244 )

namespace ph_engine {
	Player::Player(glm::vec3 posistion, float speed) {
		this->speed = speed;

		this->position = posistion;
	}
	Player::Player(float x, float y, float z, float speed) {
		this->speed = speed;

		this->position = glm::vec3(x, y, z);
	}

	void Player::move(const Keyboard& key) {
		if (key.keyPressed(GLFW_KEY_W))
			position += speed * front;

		if (key.keyPressed(GLFW_KEY_S))
			position -= speed * front;

		if (key.keyPressed(GLFW_KEY_A))
			position -= glm::normalize(glm::cross(front, up)) * speed;

		if (key.keyPressed(GLFW_KEY_D))
			position += glm::normalize(glm::cross(front, up)) * speed;
	}
	void Player::look(const Mouse& mouse) {
		double xof, yof, x, y;
		x = mouse.getX();
		y = mouse.getY();

		xof = x - lx;
		yof = ly - y;

		lx = x;
		ly = y;

		xof *= mouse.getSensitivity();
		yof *= mouse.getSensitivity();

		yaw += xof;
		pitch += yof;

		if (pitch > 89.0f) pitch = 89.0f;
		if (pitch < -89.0f) pitch = -89.0f;

		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		front = glm::normalize(front);
	}
}

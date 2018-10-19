#include "Camera.h"

#include "GLM/gtc/matrix_transform.hpp"

namespace ph_engine {
	Camera::Camera() {
		front = glm::vec3(0, 0, -1);
	}
	Camera::Camera(glm::vec3 position) {
		this->position = position;

		front = glm::vec3(0, 0, -1);
	}
	Camera::Camera(glm::vec3 position, glm::vec3 target) {
		this->position = position;

		front = target - position;
	}
	Camera::Camera(float x, float y, float z) {
		position = glm::vec3(x, y, z);

		front = glm::vec3(0, 0, -1);
	}

	void Camera::setPosition(glm::vec3 position) {
		this->position = position;
	}
	void Camera::setPosition(float x, float y, float z) {
		position = glm::vec3(x, y, z);
	}

	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(position, position + front, up);
	}

	glm::vec3 Camera::getFrontVec() {
		return front;
	}
	glm::vec3 Camera::getUp() {
		return up;
	}
	glm::vec3& Camera::getPosition() {
		return position;
	}
}

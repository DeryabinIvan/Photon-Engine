#include "stdafx.h"
#include "Camera.h"

namespace ph_engine {
	Camera::Camera() {
		up = glm::vec3(0, 1, 0);
		front = glm::vec3(0, 0, -1);
	}
	Camera::Camera(glm::vec3 position) {
		this->position = position;

		up = glm::vec3(0, 1, 0);
		front = glm::vec3(0, 0, -1);
	}
	Camera::Camera(float x, float y, float z) {
		position = glm::vec3(x, y, z);

		up = glm::vec3(0, 1, 0);
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

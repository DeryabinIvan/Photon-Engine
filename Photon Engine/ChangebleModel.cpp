#include "ChangebleModel.h"

#include "GLM/gtc/matrix_transform.hpp"

namespace ph_engine {
	void ChangebleModel::scale(float sx, float sy, float sz) {
		model = glm::scale(model, glm::vec3(sx, sy, sz));
	}

	void ChangebleModel::scale(float scale) {
		this->scale(scale, scale, scale);
	}

	void ChangebleModel::translate(float x, float y, float z) {
		model = glm::translate(model, glm::vec3(x, y, z));
	}

	void ChangebleModel::translate(glm::vec3& v) {
		model = glm::translate(model, v);
	}

	void ChangebleModel::rotate(float angle, float axisX, float axisY, float axisZ) {
		model = glm::rotate(model, angle, glm::vec3(axisX, axisY, axisZ));
	}

	void ChangebleModel::rotate(float angle, glm::vec3& axis) {
		model = glm::rotate(model, angle, axis);
	}

	const glm::mat4 ChangebleModel::getModelMatrix() {
		return model;
	}
}
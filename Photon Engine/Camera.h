#pragma once

#include "Config.h"

#include "GLM/glm.hpp"

namespace ph_engine {
	class PHOTONENGINE_API Camera {
		protected:
		glm::vec3 position, front, up;

		public:
		Camera();
		Camera(glm::vec3 position);
		Camera(float x, float y, float z);

		void setPosition(glm::vec3 position);
		void setPosition(float x, float y, float z);

		glm::mat4 getViewMatrix();

		glm::vec3 getFrontVec();
		glm::vec3 getUp();
		glm::vec3& getPosition();
	};
}


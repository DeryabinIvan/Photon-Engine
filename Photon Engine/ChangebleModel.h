#pragma once
#include "Config.h"

#include "GLM/mat4x4.hpp"

namespace ph_engine {
	class PHOTONENGINE_API ChangebleModel {
		protected:
			glm::mat4 model = glm::mat4(1.f);

		public:
			//scale X by sx, Y by sy and Z by sz
			void scale(float sx, float sy, float sz);

			//linear scale by all axes
			void scale(float scale);

			//translate model
			void translate(float x, float y, float z);

			void translate(glm::vec3& v);

			//rotate model by angle on axis
			void rotate(float angle, float axisX, float axisY, float axisZ);

			void rotate(float angle, glm::vec3& axis);

			//get model matrix
			const glm::mat4 getModelMatrix();
	};
};
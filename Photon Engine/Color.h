#pragma once
#include "Config.h"

#include "GLM/vec4.hpp"
#include "GLM/vec3.hpp"

namespace ph_engine {
	using glm::vec4;

	class PHOTONENGINE_API Color{
		vec4 color;

		Color(const vec4& vec);

		public:
			Color(float r, float g, float b, float a = 1.f);
			Color(const Color& copy);
			Color() = default;

			const Color& operator+(const Color& c) const;
			const Color& operator*(const Color& c) const;
			const vec4& toVec4() const;
			const glm::vec3& toVec3() const;
	};
}


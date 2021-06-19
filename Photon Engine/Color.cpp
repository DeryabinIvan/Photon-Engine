#include "Color.h"

namespace ph_engine {
	Color::Color(const vec4& vec){
		color = vec;
	}
	Color::Color(float r, float g, float b, float a){
		color = vec4(r, g, b, a);
	}
	Color::Color(const Color& copy){
		this->color = copy.color;
	}

	const Color& Color::operator+(const Color& c) const {
		return *(new Color(this->color + c.color));
	}
	const Color& Color::operator*(const Color& c) const {
		return *(new Color(this->color * c.color));
	}
	const glm::vec4 & Color::toVec4() const {
		return color;
	}
	const glm::vec3& Color::toVec3() const{
		return *(new glm::vec3(color.r, color.g, color.b));
	}
}
#include "Light.h"

namespace ph_engine {
	Light::Light(vec3 position, vec3 direction, Color& color, int lightType){
		if (lightType == DIRECTION)
			this->position = vec4(position, 0);
		else
			this->position = vec4(position, 1);

		this->color = color;
		this->direction = direction;
		this->lightType = lightType;
	}

	void Light::setAmbient(float a){
		ambient = vec3(a);
	}
	void Light::setDiffuse(float d){
		diffuse = vec3(d);
	}
	void Light::setSpecular(float s){
		specular = vec3(s);
	}
	void Light::setAmbient(Color& a) {
		ambient = vec3(a.toVec3());
	}
	void Light::setDiffuse(Color& d) {
		diffuse = vec3(d.toVec3());
	}
	void Light::setSpecular(Color& s) {
		specular = vec3(s.toVec3());
	}

	void Light::sendInShader(ShaderProgram& program, const std::string name){
		program.setVec4(name + ".position", position);
		program.setVec3(name + ".direction", direction);
		program.setVec3(name + ".color", color.toVec3());

		program.setVec3(name + ".ambientStrength", direction);
		program.setVec3(name + ".diffuseStrength", direction);
		program.setVec3(name + ".specularStrength", direction);
	}
	void Light::setPosition(vec3 position){
		if (lightType == DIRECTION)
			this->position = vec4(position, 0);
		else
			this->position = vec4(position, 1);
	}
	vec4& Light::getPosition(){
		return position;
	}
}

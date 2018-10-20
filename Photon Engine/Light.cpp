#include "Light.h"

#include "GLM/trigonometric.hpp"

namespace ph_engine {
	Light::Light(vec3 position, vec3 direction, Color& color, int lightType){
		if (lightType == DIRECTED)
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

	void Light::makeDot(vec3 position, Color& color){
		this->position = vec4(position, 1);
		this->color = color;

		lightType = Light::DOT;
	}

	void Light::makeDirected(vec3 direction, Color& color){
		this->position.w = 0;

		this->direction = direction;
		this->color = color;

		lightType = Light::DIRECTED;
	}

	void Light::makeSpot(vec3 position, vec3 direction, float phi, float outPhi, Color& color){
		cutOff = glm::cos(glm::radians(phi));
		outCutOff = glm::cos(glm::radians(outPhi));

		this->position = vec4(position, 1);
		this->direction = direction;
		this->color = color;

		lightType = Light::SPOT;
	}

	void Light::sendInShader(ShaderProgram& program, const std::string name){
		if (lightType != Light::DIRECTED) {
			program.setVec4(name + ".position", position);

			program.setFloat(name + ".quadratic", quadratic);
			program.setFloat(name + ".linear", linear);
			program.setFloat(name + ".constant", constant);
		}

		if (lightType != Light::DOT) {
			program.setVec3(name + ".direction", direction);
		}

		if (lightType == Light::SPOT) {
			program.setFloat(name + ".cutOff", cutOff);
			program.setFloat(name + ".outCutOff", outCutOff);
		}

		program.setVec3(name + ".color", color.toVec3());
		program.setVec3(name + ".ambientStrength", ambient);
		program.setVec3(name + ".diffuseStrength", diffuse);
		program.setVec3(name + ".specularStrength", specular);
	}
	void Light::setPosition(vec3 position){
		if (lightType == DIRECTED)
			this->position = vec4(position, 0);
		else
			this->position = vec4(position, 1);
	}
	void Light::setDirection(vec3 direction){
		this->direction = direction;
	}
	void Light::setAttenuation(float quadratic, float linear, float constant){
		this->quadratic = quadratic;
		this->linear = linear;
		this->constant = constant;
	}
	vec4& Light::getPosition(){
		return position;
	}
}

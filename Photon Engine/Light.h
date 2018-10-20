#pragma once
#include "Config.h"

#include "Color.h"
#include "ShaderProgram.h"

#include "GLM/vec3.hpp"
#include "GLM/vec4.hpp"

namespace ph_engine {
	using glm::vec3;
	using glm::vec4;

	class PHOTONENGINE_API Light{
		vec4 position;
		vec3 direction;
		Color color;

		vec3 ambient, diffuse, specular;
		float cutOff, outCutOff;
		int lightType;

		float quadratic, linear, constant;

		public:
			enum { DOT, DIRECTED, SPOT };

			Light() = default;
			Light(vec3 position, vec3 direction, Color& color, int lightType);
			
			void setAmbient(float a);
			void setDiffuse(float d);
			void setSpecular(float s);

			void setAmbient(Color& a);
			void setDiffuse(Color& d);
			void setSpecular(Color& s);

			void makeDot(vec3 position, Color& color);
			void makeDirected(vec3 direction, Color& color);
			void makeSpot(vec3 position, vec3 direction, float phi, float outPhi, Color& color);

			void sendInShader(ShaderProgram& program, const std::string name);
			
			void setPosition(vec3 position);
			void setDirection(vec3 direction);
			void setAttenuation(float quadratic, float linear, float constant);
			vec4& getPosition();
	};
}

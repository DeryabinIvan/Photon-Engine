#pragma once
#include "Config.h"

#include "Color.h"
#include "Shader IO.h"

#include "GLM/vec3.hpp"
#include "GLM/vec4.hpp"

namespace ph_engine {
	using glm::vec3;
	using glm::vec4;

	enum LigthType{ DOT, DIRECTED, SPOT, NONE };

	class PHOTONENGINE_API Light:ShaderIO{
		vec4 position;
		vec3 direction;
		Color color;

		vec3 ambient, diffuse, specular;
		float cutOff, outCutOff;
		LigthType lType;

		float quadratic, linear, constant;

		public:
			Light() : ambient(0, 0, 0),
				diffuse(0, 0, 0),
				specular(0, 0, 0),
				color(0, 0, 0),
				cutOff(0),
				outCutOff(0),
				lType(LigthType::NONE),
				direction(0, 0, 0),
				position(0, 0, 0, 0),
				linear(0), quadratic(0), constant(0)
			{};

			Light(vec3 position, vec3 direction, Color& color, LigthType lightType);
			
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

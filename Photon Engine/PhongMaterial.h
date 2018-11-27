#pragma once
#include "Config.h"
#include "Shader IO.h"

#include "Texture.h"

#include "GLM/vec3.hpp"

namespace ph_engine {
	class PHOTONENGINE_API PhongMaterial:ShaderIO {
		glm::vec3 ambient, diffuse, specular;
		float shininess;

		Texture *diff, *spec;
		int diffBlock, specBlock;

		public:
			~PhongMaterial();

			void setAmbient(float r, float g, float b);
			void setDiffuse(float r, float g, float b);
			void setSpecular(float r, float g, float b);

			void setAmbient(float ambient);
			void setDiffuse(float diffuse);
			void setSpecular(float specular);

			void setShininess(float s);

			void loadDiffuse(std::string path, int block);
			void loadSpecular(std::string path, int block);
			void activeDiffuse();
			void activeSpecular();
			
			// Inherited via ShaderIO
			virtual void sendInShader(ShaderProgram& program, const std::string name) override;
	};
}

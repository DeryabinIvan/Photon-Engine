#pragma once
#include "Config.h"
#include "Shader IO.h"

#include "Texture.h"

#include "GLM/vec3.hpp"

namespace ph_engine {
	class PHOTONENGINE_API PhongMaterial:ShaderIO {
		glm::vec3 ambient = glm::vec3(0), 
				  diffuse = glm::vec3(0),
				  specular = glm::vec3(0);
		float shininess = 64;

		Texture diffuseMap, specularMap;
		int diffBlock = -1, specBlock = -1;

		public:
			PhongMaterial();

			void setAmbient(float r, float g, float b);
			void setDiffuse(float r, float g, float b);
			void setSpecular(float r, float g, float b);

			void setAmbient(float ambient);
			void setDiffuse(float diffuse);
			void setSpecular(float specular);

			void setDiffuse(Texture diffuse);
			void setSpecular(Texture specular);

			void setShininess(float s);

			//Textures maps
			void loadDiffuse(std::string path, int block);
			void loadSpecular(std::string path, int block);
			void activeDiffuse();
			void activeSpecular();

			bool haveDiffuseMap() const;
			bool haveSpecularMap() const;
			
			// Inherited via ShaderIO
			virtual void sendInShader(ShaderProgram& program, const std::string name) override;
	};
}

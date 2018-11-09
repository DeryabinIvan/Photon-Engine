#include "PhongMaterial.h"

namespace ph_engine {
	PhongMaterial::~PhongMaterial(){
		if (diff) delete diff;
		if (spec) delete spec;
	}

	void PhongMaterial::setAmbient(float r, float g, float b){
		ambient = glm::vec3(r, g, b);
	}
	void PhongMaterial::setDiffuse(float r, float g, float b){
		diffuse = glm::vec3(r, g, b);
	}
	void PhongMaterial::setSpecular(float r, float g, float b){
		specular = glm::vec3(r, g, b);
	}
	void PhongMaterial::setAmbient(float a) {
		ambient = glm::vec3(a);
	}
	void PhongMaterial::setDiffuse(float d) {
		diffuse = glm::vec3(d);
	}
	void PhongMaterial::setSpecular(float s) {
		specular = glm::vec3(s);
	}

	void PhongMaterial::setShininess(float s){
		shininess = s;
	}

	void PhongMaterial::loadDiffuse(std::string path, int block){
		diff = new Texture();
		diff->loadFromFile(path.c_str(), Texture::DIFFUSE);
		diffBlock = block;

		diffuse = glm::vec3(-1);
	}
	void PhongMaterial::loadSpecular(std::string path, int block){
		spec = new Texture();
		spec->loadFromFile(path.c_str(), Texture::SPECULAR);
		specBlock = block;

		specular = glm::vec3(-1);
	}

	void PhongMaterial::activeDiffuse(){
		diff->activeTexture(diffBlock);
		diff->bind();
	}

	void PhongMaterial::activeSpecular(){
		spec->activeTexture(specBlock);
		spec->bind();
	}

	void PhongMaterial::sendInShader(ShaderProgram& program, const std::string name){
		program.setVec3(name + ".ambient", ambient);
		program.setFloat(name + ".shininess", shininess);

		if(diffuse.x != -1) program.setVec3(name + ".diffuse", diffuse);
		else program.setInt(name + ".diffuse", diffBlock);

		if(specular.x != -1) program.setVec3(name + ".specular", specular);
		else program.setInt(name + ".specular", specBlock);
	}
}

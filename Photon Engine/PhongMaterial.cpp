#include "PhongMaterial.h"

namespace ph_engine {
	PhongMaterial::PhongMaterial(){
		ambient = glm::vec3(.2f);
		diffuse = glm::vec3(.2f);
		specular = glm::vec3(.2f);

		shininess = 1;
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

	void PhongMaterial::setDiffuse(Texture diffuse) {
		diffuseMap = diffuse;
	}

	void PhongMaterial::setSpecular(Texture specular) {
		specularMap = specular;
	}

	void PhongMaterial::setNormal(Texture normal) {
		normalMap = normal;
	}

	void PhongMaterial::setShininess(float s){
		shininess = s;
	}

	void PhongMaterial::loadDiffuse(std::string path, int block){
		diffuseMap.loadFromFile(path.c_str());
		diffBlock = block;
	}
	void PhongMaterial::loadSpecular(std::string path, int block){
		specularMap.loadFromFile(path.c_str());
		specBlock = block;
	}

	void PhongMaterial::loadNormal(std::string path, int block) {
		specularMap.loadFromFile(path.c_str());
		specBlock = block;
	}

	void PhongMaterial::activeDiffuse(){
		diffuseMap.activeTexture(diffBlock);
		diffuseMap.bind();
	}
	void PhongMaterial::activeSpecular(){
		specularMap.activeTexture(specBlock);
		specularMap.bind();
	}

	void PhongMaterial::activeNormal() {
		normalMap.activeTexture(normalBlock);
		normalMap.bind();
	}

	bool PhongMaterial::haveDiffuseMap() const{
		return (diffBlock != -1);
	}

	bool PhongMaterial::haveSpecularMap() const{
		return (specBlock != -1);
	}

	bool PhongMaterial::haveNormalMap() const {
		return (normalBlock != -1);
	}

	void PhongMaterial::sendInShader(ShaderProgram& program, const std::string name){
		program.setVec3(name + ".ambient", ambient);
		program.setFloat(name + ".shininess", shininess);

		if (diffBlock == -1) {
			program.setVec3(name + ".diffuse", diffuse);
		} else {
			program.setInt(name + ".diffuse", diffBlock);
		}

		if(specBlock == -1) {
			program.setInt(name + ".specular", diffBlock);
		} else {
			program.setInt(name + ".specular", specBlock);
		}

		if (haveNormalMap()) {
			program.setInt(name + ".normal", normalBlock);
		}
	}
}

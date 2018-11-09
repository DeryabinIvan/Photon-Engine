#include "Model.h"

#include "GLEW/glew.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "SOIL/SOIL.h"

namespace ph_engine {
	Model::Model(){
		model = glm::mat4(1.f);
	}

	Model::~Model(){
		//todo AssImp unload
	}

	void Model::draw(ShaderProgram& program) {
		for (uint i = 0; i < meshes.size(); i++)
			meshes[i].draw(program);
	}

	void Model::load(string path) {
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

		if (!scene || scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cerr << "Model load error: " << import.GetErrorString() << std::endl;
			return;
		}

		dir = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);

#ifdef _DEBUG
		std::cout << "Loaded textures:" << std::endl;
		for (unsigned int j = 0; j < textures_loaded.size(); j++) {
			std::cout << textures_loaded[j] << std::endl;
		}
#endif
	}

	void Model::scale(float sx, float sy, float sz){
		model = glm::scale(model, glm::vec3(sx, sy, sz));
	}
	void Model::scale(float s) {
		model = glm::scale(model, glm::vec3(s, s, s));
	}

	void Model::translate(float x, float y, float z){
		model = glm::translate(model, glm::vec3(x, y, z));
	}

	void Model::rotate(float angle, float axisX, float axisY, float axisZ){
		model = glm::rotate(model, angle, glm::vec3(axisX, axisY, axisZ));
	}

	const glm::mat4 Model::getModelMatrix(){
		return model;
	}

	void Model::processNode(aiNode* node, const aiScene* scene) {
		for (uint i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		for (uint i = 0; i < node->mNumChildren; i++)
			processNode(node->mChildren[i], scene);
	}

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
		vector<Mesh::Vertex> verticies;
		vector<uint> indices;
		vector<Texture> textures;

		for (uint i = 0; i < mesh->mNumVertices; i++) {
			Mesh::Vertex vertex;
			
			glm::vec3 tmp;
			tmp.x = mesh->mVertices[i].x;
			tmp.y = mesh->mVertices[i].y;
			tmp.z = mesh->mVertices[i].z;
			vertex.position = tmp;

			tmp.x = mesh->mNormals[i].x;
			tmp.y = mesh->mNormals[i].y;
			tmp.z = mesh->mNormals[i].z;
			vertex.normal = tmp;

			if (mesh->mTextureCoords[0]) {
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.texCoord = vec;
			} else {
				vertex.texCoord = glm::vec2(0.f);
			}

			verticies.push_back(vertex);
		}

		for (uint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (uint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		if (mesh->mMaterialIndex >= 0) {
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(verticies, indices, textures);
	}

	vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
		vector<Texture> textures;
		
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
			
			aiString path;
			mat->GetTexture(type, i, &path);
			bool skip = false;

			for (unsigned int j = 0; j < textures_loaded.size(); j++) {
				if (std::strcmp(textures_loaded[j].c_str(), path.C_Str()) == 0) {
					skip = true;
					break;
				}
			}
			// ���� �������� �� ���� ���������
			if (!skip) {
				Texture texture;
				string filename = dir + '/' + path.C_Str();

				texture.loadFromFile(filename.c_str(), Texture::TEXTURE_TYPE(type));
				textures.push_back(texture);
				// ������� �������� � ������ ��� �����������
				textures_loaded.push_back(path.C_Str());
			}
		}
		return textures;
	}
}
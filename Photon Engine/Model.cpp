#include "Model.h"

#include "GLEW/glew.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

namespace ph_engine {
	Model::Model(){

	}

	Model::~Model(){
		//TODO: AssImp unload
	}

	void Model::draw(ShaderProgram& program) {
		for (int i = 0; i < meshes.size(); i++)
			meshes[i].draw(program);
	}

	void Model::loadModel(string path) {
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

	void Model::processNode(aiNode* node, const aiScene* scene) {
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			Mesh current = processMesh(mesh, scene);

			if (mesh->mMaterialIndex) {
				aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
				string diffusePath, specularPath;

				diffusePath = getTexturePath(material, aiTextureType_DIFFUSE);
				specularPath = getTexturePath(material, aiTextureType_SPECULAR);

				//meshes.back().loadTextures(diffusePath, specularPath);
				current.loadTexture(Texture::TEXTURE_TYPE::DIFFUSE, diffusePath, 0);
				current.loadTexture(Texture::TEXTURE_TYPE::SPECULAR, specularPath, 1);
			}

			meshes.push_back(current);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
			processNode(node->mChildren[i], scene);
	}

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
		vector<Mesh::Vertex> verticies;
		vector<int> indices;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
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

		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		
		return Mesh(verticies, indices);
	}

	string Model::getTexturePath(aiMaterial* mat, aiTextureType type) {		
		aiString path;
		mat->GetTexture(type, 0, &path);
		bool skip = false;

		for (unsigned int j = 0; j < textures_loaded.size(); j++) {
			if (std::strcmp(textures_loaded[j].c_str(), path.C_Str()) == 0) {
				skip = true;
				break;
			}
		}
		if (!skip && path.length) {
			string texturepath = dir + '/' + path.C_Str();
			textures_loaded.push_back(texturepath);
			return texturepath;
		}
		
		return string();
	}
}
#include "stdafx.h"
#include "Model.h"

namespace ph_engine {
	void Model::draw(ShaderProgram& program) {
		for (uint i = 0; i < meshes.size(); i++)
			meshes[i].draw(program);
	}

	void Model::load(string path) {
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cerr << "Model load error: " << import.GetErrorString() << std::endl;
			return;
		}

		dir = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
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
		vector<Vertex> verticies;
		vector<uint> indices;
		vector<TextureStruct> textures;

		for (uint i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			
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
			vector<TextureStruct> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<TextureStruct> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(verticies, indices, textures);
	}

	vector<TextureStruct> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
		vector<TextureStruct> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++) {
				if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0) {
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip) {   // если текстура не была загружена – сделаем это
				TextureStruct texture;
				texture.id = TextureFromFile(str.C_Str(), dir);
				texture.type = typeName;
				texture.path = str;
				textures.push_back(texture);
				// занесем текстуру в список уже загруженных
				textures_loaded.push_back(texture);
			}
		}
		return textures;
	}

	unsigned int TextureFromFile(const char* path, const string& directory, bool gamma) {
		string filename = string(path);
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char *data = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		if (data) {
			GLenum format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			SOIL_free_image_data(data);
		} else {
			std::cout << "Texture failed to load at path: " << path << std::endl;
			SOIL_free_image_data(data);
		}

		return textureID;
	}
}
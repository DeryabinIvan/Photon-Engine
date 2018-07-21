#pragma once

#include "stdafx.h"

#include "Mesh.h"
#include "ShaderProgram.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include <vector>
#include <iostream>

using std::vector;
using std::string;

namespace ph_engine {
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

	class PHOTONENGINE_API Model {
		public:
			Model();
			void draw(ShaderProgram& program);
			void load(string path);

			void scale(float sx, float sy, float sz);
			void scale(float scale);
			void translate(float x, float y, float z);
			void rotate(float angle, glm::vec3 axis);
			void rotate(float angle, float axisX, float axisY, float axisZ);
			const glm::mat4 getModelMatrix();
		private:
			vector<Mesh> meshes;
			vector<TextureStruct> textures_loaded;
			string dir;
			glm::mat4 model;

			void processNode(aiNode* node, const aiScene* scene);
			Mesh processMesh(aiMesh* mesh, const aiScene* scene);
			vector<TextureStruct> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	};
}

#pragma once

#include "Config.h"

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
	class PHOTONENGINE_API Model {
		public:
			Model();
			~Model();
			void draw(ShaderProgram& program);
			void load(string path);

			void scale(float sx, float sy, float sz);
			void scale(float scale);
			void translate(float x, float y, float z);
			void rotate(float angle, float axisX, float axisY, float axisZ);
			const glm::mat4 getModelMatrix();
		private:
			vector<Mesh> meshes;
			vector<string> textures_loaded;
			string dir;
			glm::mat4 model;

			void processNode(aiNode* node, const aiScene* scene);
			Mesh processMesh(aiMesh* mesh, const aiScene* scene);
			vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	};
}

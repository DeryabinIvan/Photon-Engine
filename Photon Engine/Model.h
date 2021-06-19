#pragma once

#include "Config.h"

#include "ChangebleModel.h"
#include "Mesh.h"
#include "PhongMaterial.h"
#include "ShaderProgram.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include <vector>
#include <iostream>

using std::vector;
using std::string;

namespace ph_engine {
	class PHOTONENGINE_API Model : public ChangebleModel {
		public:
			Model();
			~Model();
			void draw(ShaderProgram& program);
			void loadModel(string path);

		private:
			vector<Mesh> meshes;
			vector<string> textures_loaded;
			string dir;

			void processNode(aiNode* node, const aiScene* scene);
			Mesh processMesh(aiMesh* mesh, const aiScene* scene);
			string getTexturePath(aiMaterial* mat, aiTextureType type);
	};
}

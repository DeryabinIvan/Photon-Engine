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
		void draw(ShaderProgram& program);
		void load(string path);

		private:
		vector<Mesh> meshes;
		vector<TextureStruct> textures_loaded;
		string dir;

		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		vector<TextureStruct> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	};
}

#pragma once

#include "Config.h"
#include <vector>
#include <sstream>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"

#include "assimp/scene.h"

using std::vector;
using std::string;
using std::stringstream;

namespace ph_engine {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	struct TextureStruct {
		unsigned int id;
		std::string type;
		aiString path;
	};

	typedef unsigned int uint;

	class Mesh {
		public:
		vector<Vertex> vert;
		vector<uint> ind;
		vector<TextureStruct> tex;

		Mesh(vector<Vertex> v, vector<uint> i, vector<TextureStruct> t);
		void draw(ShaderProgram& program);

		private:
		VAO* vao;
		VBO* vbo;
		EBO* ebo;

		void setup();
	};
}

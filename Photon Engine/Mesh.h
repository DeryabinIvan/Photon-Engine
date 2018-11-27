#pragma once

#include "Config.h"
#include <vector>
#include <sstream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include "assimp/scene.h"

using std::vector;
using std::string;
using std::stringstream;

namespace ph_engine {
	class PHOTONENGINE_API Mesh {
		public:
			struct Vertex {
				glm::vec3 position;
				glm::vec3 normal;
				glm::vec2 texCoord;
			};

			vector<Vertex> vert;
			vector<uint> ind;
			vector<Texture> tex;

			Mesh(vector<Vertex> v, vector<uint> i, vector<Texture> t);
			void draw(ShaderProgram& program);

		private:
			VertexArray* vao;
			VertexBuffer* vbo;
			ElementBuffer* ebo;

			void setup();
	};
}

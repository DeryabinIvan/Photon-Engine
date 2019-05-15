#pragma once

#include "Config.h"
#include <vector>
#include <sstream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "PhongMaterial.h"

#include "assimp/scene.h"

namespace ph_engine {
	using std::vector;
	using std::string;
	using std::stringstream;

	class PHOTONENGINE_API Mesh {
		public:
			struct Vertex {
				glm::vec3 position;
				glm::vec3 normal;
				glm::vec2 texCoord;
			};

			Mesh(vector<Vertex> v, vector<uint> i);
			void loadTextures(string diffuse, string specular);
			void draw(ShaderProgram& program);

		private:
			vector<Vertex> vert;
			vector<uint> ind;
			PhongMaterial material;

			VertexArray* vao;
			VertexBuffer* vbo;
			ElementBuffer* ebo;

			void setup();
	};
}

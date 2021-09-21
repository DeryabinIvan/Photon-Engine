#pragma once

#include "Config.h"
#include <vector>
#include <sstream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "MeshDataOffsets.h"
#include "ChangebleModel.h"

#include "ShaderProgram.h"
#include "Texture.h"
#include "PhongMaterial.h"

#include "assimp/scene.h"

namespace ph_engine {
	using std::vector;
	using std::string;
	using std::stringstream;

	class PHOTONENGINE_API Mesh : public ChangebleModel {
		public:
			struct Vertex {
				glm::vec3 position;
				glm::vec3 normal;
				glm::vec2 texCoord;
			};

			Mesh(MeshDataHelper &off, const void* raw_data, size_t elements);
			Mesh(vector<Vertex> &vert, vector<int> &ind);

			void loadTexture(Texture::TEXTURE_TYPE type, string path, int block);

			void draw(ShaderProgram& program);

		private:
			size_t indSize = 0;
			PhongMaterial material;
			
			size_t vertexCount = 0;

			VertexArray* vao;
			VertexBuffer* vbo;
			ElementBuffer* ebo;
	};
}

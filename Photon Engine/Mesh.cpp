#include "Mesh.h"

#include "GLEW/glew.h"

namespace ph_engine {
	Mesh::Mesh(vector<Vertex> v, vector<uint> i){
		vert = v;
		ind = i;

		setup();
	}

	void Mesh::loadTextures(string diffuse, string specular){
		if (!diffuse.empty())
			material.loadDiffuse(diffuse, 0);

		if (!specular.empty())
			material.loadSpecular(specular, 1);

		material.setShininess(16);
	}

	void Mesh::draw(ShaderProgram& program) {
		material.activeDiffuse();
		if(material.haveSpecularMap())
			material.activeSpecular();

		material.sendInShader(program, "material");

		Texture::activeTexture(0);

		vao->bind();
			glDrawElements(GL_TRIANGLES, ind.size(), GL_UNSIGNED_INT, 0);
		vao->unbind();
	}

	void Mesh::setup() {
		vbo = new VertexBuffer();
		vao = new VertexArray();
		ebo = new ElementBuffer();

		vao->bind();
			vbo->bind();
				vbo->load(vert.size() * sizeof(Vertex), &vert[0]);

				ebo->bind();
					ebo->load(ind.size() * sizeof(uint), &ind[0]);

				//positions
				vbo->enableAttrib(0);
				vbo->addVertexAttrib(0, 3, GL_FALSE, sizeof(Vertex), static_cast<void*>(0));

				//normals
				vbo->enableAttrib(1);
				vbo->addVertexAttrib(1, 3, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

				//texture coordinates
				vbo->enableAttrib(2);
				vbo->addVertexAttrib(2, 2, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
			vao->unbind();
		ebo->unbind();
	}
}

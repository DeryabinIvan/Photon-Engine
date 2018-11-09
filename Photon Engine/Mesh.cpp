#include "Mesh.h"

#include "GLEW/glew.h"

ph_engine::Mesh::Mesh(vector<Vertex> v, vector<uint> i, vector<Texture> t) {
	vert = v;
	ind = i;
	tex = t;

	setup();
}

void ph_engine::Mesh::draw(ShaderProgram& program) {
	for (uint i = 0; i < tex.size(); i++) {
		Texture::activeTexture(i);

		//for lighting not using now...
		Texture::TEXTURE_TYPE name = tex[i].getType();

		switch (name){
			case Texture::DIFFUSE:
				program.setInt("material.diffuse", i);
				break;
			case Texture::SPECULAR:
				program.setInt("material.specular", i);
				break;
		}
		
		tex[i].bind();
	}
	Texture::activeTexture(0);

	vao->bind();
	glDrawElements(GL_TRIANGLES, ind.size(), GL_UNSIGNED_INT, 0);
	vao->unbind();
}

void ph_engine::Mesh::setup() {
	vbo = new VBO();
	vao = new VAO();
	ebo = new EBO();

	vao->bind();
	vbo->bind();
	vbo->load(vert.size() * sizeof(Vertex), &vert[0]);

	ebo->bind();
	ebo->load(ind.size() * sizeof(uint), &ind[0]);

	//positions
	vbo->enableAttrib(0);
	vbo->addVertexAttrib(0, 3, GL_FALSE, sizeof(Vertex), (void*) 0);

	//normals
	vbo->enableAttrib(1);
	vbo->addVertexAttrib(1, 3, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//texture coordinates
	vbo->enableAttrib(2);
	vbo->addVertexAttrib(2, 2, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	vao->unbind();

	ebo->unbind();
}

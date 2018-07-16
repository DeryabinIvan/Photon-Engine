#include "stdafx.h"
#include "Mesh.h"

ph_engine::Mesh::Mesh(vector<Vertex> v, vector<uint> i, vector<TextureStruct> t) {
	vert = v;
	ind = i;
	tex = t;

	setup();
}

void ph_engine::Mesh::draw(ShaderProgram& program) {
	uint diffuse = 1, specular = 1;

	for (uint i = 0; i < tex.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		//for lighting not using now...
		stringstream ss;
		string number, name = tex[i].type;
		if (name == "texture_diffuse") ss << diffuse++;
		else if (name == "texture_specular") ss << specular++;
		number = ss.str();

		program.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, tex[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

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
	vbo->addVertexAttrib(1, 3, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

	//texture coordinates
	vbo->enableAttrib(2);
	vbo->addVertexAttrib(2, 2, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));

	vao->unbind();
	ebo->unbind();
}

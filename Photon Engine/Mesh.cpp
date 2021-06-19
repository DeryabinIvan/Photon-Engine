#include "Mesh.h"

#include "GLEW/glew.h"

namespace ph_engine {
	Mesh::Mesh(vector<Vertex>& vert, vector<uint>& ind) {
		indSize = ind.size();

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

	//???
	Mesh::Mesh(MeshDataHelper off, const void* raw_data, size_t size) {
		vbo = new VertexBuffer();
		vao = new VertexArray();

		vector<float> vec_ind, vec_data;
		bool _ind = off.hasIndex();
		uint step_offset = off.getVertex().second + off.getNormal().second + off.getColor().second + off.getTexture().second;

		float* _data = ((float*) raw_data);

		if (_ind) {
			ebo = new ElementBuffer();

			//parsing raw data
			for (int i = 0; i < size; i += off.getIndex().first)
				vec_ind.push_back(_data[i]);

			indSize = vec_ind.size();
		}

		if (_ind) {
			for (int i = 0; i < size; i++)
				if (i % off.getIndex().first)
					vec_data.push_back(_data[i]);
		} else {
			for (int i = 0; i < size; i++)
				vec_data.push_back(_data[i]);
		}

		vertexCount = vec_data.size() / step_offset;

		//init VAO, VBO, EBO...
		int attrib = 0;
		uint stride = sizeof(float) * step_offset;

		vao->bind();
		vbo->bind();

		vbo->load(vec_data.size() * sizeof(float), &vec_data[0]);

		if (_ind) {
			ebo->bind();
			ebo->load(vec_ind.size() * sizeof(uint), &vec_ind[0]);
		}

		//position
		if (off.hasVertex()) {
			vbo->enableAttrib(attrib);
			vbo->addVertexAttrib(attrib++, off.getVertex().second, false, stride, static_cast<void*>(0));
		}

		//normal
		if (off.hasNormal()) {
			vbo->enableAttrib(attrib);
			vbo->addVertexAttrib(attrib++, off.getNormal().second, false, stride, reinterpret_cast<void*>(off.getNormal().first * sizeof(float)));
		}

		//color
		if (off.hasColor()) {
			vbo->enableAttrib(attrib);
			vbo->addVertexAttrib(attrib++, off.getColor().second, false, stride, reinterpret_cast<void*>(off.getColor().first * sizeof(float)));
		}

		//texture
		if (off.hasTexture()) {
			vbo->enableAttrib(attrib);
			vbo->addVertexAttrib(attrib++, off.getTexture().second, false, stride, reinterpret_cast<void*>(off.getTexture().first * sizeof(float)));
		}

		if (_ind)
			ebo->unbind();

		vbo->unbind();
		vao->unbind();
	}

	void Mesh::loadTextures(string diffuse, string specular) {
		if (!diffuse.empty())
			material.loadDiffuse(diffuse, 0);

		if (!specular.empty())
			material.loadSpecular(specular, 1);

		material.setShininess(16);
	}

	void Mesh::draw(ShaderProgram& program) {
		if (material.haveDiffuseMap()) {
			material.activeDiffuse();
			if (material.haveSpecularMap())
				material.activeSpecular();

			material.sendInShader(program, "material");
		}

		Texture::activeTexture(0);

		if (indSize == 0) {
			vao->bind();
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
			vao->unbind();
		} else {
			vao->bind();
			glDrawElements(GL_TRIANGLES, indSize, GL_UNSIGNED_INT, 0);
			vao->unbind();
		}
	}
}

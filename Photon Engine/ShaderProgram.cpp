#include "ShaderProgram.h"

#include "GLEW/glew.h"
#include "GLM/vec2.hpp"
#include "GLM/vec3.hpp"
#include "GLM/mat2x2.hpp"
#include "GLM/mat3x3.hpp"
#include "GLM/mat4x4.hpp"

#ifdef _DEBUG
#include <iostream>
using std::cerr;
using std::endl;
#endif

namespace ph_engine {
	ShaderProgram::ShaderProgram() {
		objectID = glCreateProgram();
	}

	void ShaderProgram::addShader(Shader& s) {
		glAttachShader(objectID, s.getID());
	}
	bool ShaderProgram::link() {
		glLinkProgram(objectID);

		GLint result;
		glGetProgramiv(objectID, GL_COMPILE_STATUS, &result);

		if (!result) {
#ifdef _DEBUG
			GLchar errorLog[512];
			glGetProgramInfoLog(objectID, 512, nullptr, errorLog);

			std::cerr << "Compile shader error:\n" << errorLog << std::endl;
#endif
			return false;
		}
		return true;
	}

	GLint ShaderProgram::getUniformLocation(const char* name) {
		return glGetUniformLocation(objectID, name);
	}

	void ShaderProgram::use() {
		glUseProgram(objectID);
	}
	bool ShaderProgram::isUniformExist(const std::string& name) const {
		return (glGetUniformLocation(objectID, name.c_str()) != -1);
	}

	void ShaderProgram::setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(objectID, name.c_str()), (int)value);
	}
	void ShaderProgram::setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(objectID, name.c_str()), value);
	}
	void ShaderProgram::setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(objectID, name.c_str()), value);
	}
	void ShaderProgram::setVec2(const std::string &name, const glm::vec2 &value) const {
		glUniform2fv(glGetUniformLocation(objectID, name.c_str()), 1, &value[0]);
	}
	void ShaderProgram::setVec2(const std::string &name, float x, float y) const {
		glUniform2f(glGetUniformLocation(objectID, name.c_str()), x, y);
	}
	void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value) const {
		glUniform3fv(glGetUniformLocation(objectID, name.c_str()), 1, &value[0]);
	}
	void ShaderProgram::setVec3(const std::string &name, float x, float y, float z) const {
		glUniform3f(glGetUniformLocation(objectID, name.c_str()), x, y, z);
	}
	void ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value) const {
		glUniform4fv(glGetUniformLocation(objectID, name.c_str()), 1, &value[0]);
	}
	void ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w) {
		glUniform4f(glGetUniformLocation(objectID, name.c_str()), x, y, z, w);
	}
	void ShaderProgram::setMat2(const std::string &name, const glm::mat2 &mat) const {
		glUniformMatrix2fv(glGetUniformLocation(objectID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void ShaderProgram::setMat3(const std::string &name, const glm::mat3 &mat) const {
		glUniformMatrix3fv(glGetUniformLocation(objectID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const {
		glUniformMatrix4fv(glGetUniformLocation(objectID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
}

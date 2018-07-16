#include "stdafx.h"
#include "ShaderProgram.h"

#include <iostream>

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
			GLchar errorLog[512];
			glGetProgramInfoLog(objectID, 512, nullptr, errorLog);

			std::cerr << "Compile shader error:\n" << errorLog << std::endl;
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
	bool ShaderProgram::isUniformExist(const std::string& name) {
		return (glGetUniformLocation(objectID, name.c_str()) != -1);
	}
}

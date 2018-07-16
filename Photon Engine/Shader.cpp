#include "stdafx.h"
#include "Shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace ph_engine {
	bool Shader::loadFromStr(const char * str, SHADER_TYPE type) {
		objectID = glCreateShader(type == VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		//Load shader from string...
		glShaderSource(objectID, 1, &str, nullptr);
		glCompileShader(objectID);

		GLint result;
		glGetShaderiv(objectID, GL_COMPILE_STATUS, &result);
		if (!result) {
			GLchar errorLog[512];
			glGetShaderInfoLog(objectID, 512, nullptr, errorLog);

			std::cerr << "Compile shader error:\n" << errorLog << std::endl;
			return false;
		}

		return true;
	}
	bool Shader::loadFromFile(const char * filename, SHADER_TYPE type) {
		objectID = glCreateShader(type == VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		//Load shader from file...
		ifstream file(filename);
		string code;

		try {
			stringstream strStream;
			strStream << file.rdbuf();

			file.close();

			code = strStream.str();
		} catch (const std::exception&) {
			cerr << "Error load shader from file '" << filename << "'\n";
		}
		const GLchar* glCode = code.c_str();

		glShaderSource(objectID, 1, &glCode, NULL);
		glCompileShader(objectID);

		GLint result;
		glGetShaderiv(objectID, GL_COMPILE_STATUS, &result);
		if (!result) {
			GLchar errorLog[512];
			glGetShaderInfoLog(objectID, 512, nullptr, errorLog);

			std::cerr << "Compile shader error:\n" << errorLog << std::endl;
			return false;
		}

		return true;
	}

	//This function delete shader
	//If you already link shaders in program
	//use this fuction
	void Shader::remove() {
		glDeleteShader(objectID);
	}
}

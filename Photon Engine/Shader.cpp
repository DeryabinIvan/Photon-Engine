#include "Shader.h"

#include "GLEW/glew.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace ph_engine {
	bool Shader::loadFromStr(const char * str, SHADER_TYPE type) {
		switch (type) {
			case VERTEX:
				objectID = glCreateShader(GL_VERTEX_SHADER);
				break;
			case FRAGMENT:
				objectID = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			case GEOMETRY:
				objectID = glCreateShader(GL_GEOMETRY_SHADER);
				break;
		}

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
		switch (type) {
			case VERTEX:
				objectID = glCreateShader(GL_VERTEX_SHADER);
				break;
			case FRAGMENT:
				objectID = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			case GEOMETRY:
				objectID = glCreateShader(GL_GEOMETRY_SHADER);
				break;
		}

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
#ifdef _DEBUG
			GLchar errorLog[512];
			glGetShaderInfoLog(objectID, 512, nullptr, errorLog);

			std::cerr << "Compile shader error:\n" << errorLog << std::endl;
#endif // _DEBUG
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

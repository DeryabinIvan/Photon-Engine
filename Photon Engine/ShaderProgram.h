#pragma once

#include "Config.h"

#include "GLObject.h"
#include "Shader.h"

#include "GLM/vec2.hpp"
#include "GLM/vec3.hpp"
#include "GLM/mat2x2.hpp"
#include "GLM/mat3x3.hpp"
#include "GLM/mat4x4.hpp"

#include <string>

namespace ph_engine {
	class PHOTONENGINE_API ShaderProgram:GLObject {

		public:
		ShaderProgram();
		void addShader(Shader& s);
		bool link();

		int getUniformLocation(const char* name);

		void use();

		bool isUniformExist(const std::string& name) const;
		// utility uniform functions
		// ------------------------------------------------------------------------
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		// ------------------------------------------------------------------------
		void setVec2(const std::string &name, const glm::vec2 &value) const;
		void setVec2(const std::string &name, float x, float y) const;
		// ------------------------------------------------------------------------
		void setVec3(const std::string &name, const glm::vec3 &value) const;
		void setVec3(const std::string &name, float x, float y, float z) const;
		// ------------------------------------------------------------------------
		void setVec4(const std::string &name, const glm::vec4 &value) const;
		void setVec4(const std::string &name, float x, float y, float z, float w);
		// ------------------------------------------------------------------------
		void setMat2(const std::string &name, const glm::mat2 &mat) const;
		void setMat3(const std::string &name, const glm::mat3 &mat) const;
		void setMat4(const std::string &name, const glm::mat4 &mat) const;
		// ------------------------------------------------------------------------
	};
}

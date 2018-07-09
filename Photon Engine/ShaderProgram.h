#pragma once

#include "GLObject.h"

#include "Shader.h"

namespace ph_engine {
	class PHOTONENGINE_API ShaderProgram:GLObject {

		public:
		ShaderProgram();
		void addShader(Shader& s);
		bool link();

		GLint getUniformLocation(const char* name);

		// Inherited via GLObject
		virtual void bind() override;
		virtual void unbind() override;
	};
}

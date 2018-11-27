#pragma once
#include "Config.h"

#include "ShaderProgram.h"

namespace ph_engine {
	class ShaderIO {
		public:
			virtual void sendInShader(ShaderProgram& program, const std::string name) = 0;
	};
}
#pragma once

# include "../../macro.hpp"

class Shader {
	private:
		unsigned int	_shaderProgram;
		unsigned int	_vertexShader;
		unsigned int	_fragmentShader;
	public:
		Shader();
		~Shader();

	void use() const;
	const unsigned int &getProgram();
};
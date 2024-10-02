#pragma once

# include "../macro.hpp"

class Draw {
	private:
		unsigned int 	_shaderProgram;
		unsigned int 	_VAO, _VBO;
	public:
		Draw();
		~Draw();

		void drawing();

		unsigned int &getShaderProgram();
		unsigned int &getVAO();
		unsigned int &getVBO();
};
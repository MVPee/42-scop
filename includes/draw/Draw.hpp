#pragma once

# include "../macro.hpp"

class Draw {
	private:
		unsigned int 	_shaderProgram;
		unsigned int 	_VAO, _VBO;

		Draw(const Draw &ref);
		Draw &operator=(const Draw &ref);
	public:
		Draw();
		~Draw();

		unsigned int &getShaderProgram();
		unsigned int &getVAO();
		unsigned int &getVBO();
};

std::ostream &operator<<(std::ostream &o, const Draw &i);
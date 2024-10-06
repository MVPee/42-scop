#pragma once

# include "../macro.hpp"

class Camera;

class Draw {
	private:
		unsigned int 				_shaderProgram;
		unsigned int 				_VAO, _VBO, _EBO;
		std::vector<float>			_vertices;
		std::vector<unsigned int>	_indices;
		Camera						*_camera;

		void parseObject(std::ifstream &file);
	public:
		Draw(Camera *camera, std::ifstream &file);
		~Draw();

		void drawing();

		unsigned int &getShaderProgram();
		unsigned int &getVAO();
		unsigned int &getVBO();
};
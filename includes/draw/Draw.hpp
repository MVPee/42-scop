#pragma once

# include "../macro.hpp"

class Camera;

class Draw {
	private:
		unsigned int 	_shaderProgram;
		unsigned int 	_VAO, _VBO, _EBO;
		Camera			*_camera;
	public:
		Draw(Camera *camera);
		~Draw();

		void drawing();

		unsigned int &getShaderProgram();
		unsigned int &getVAO();
		unsigned int &getVBO();
};
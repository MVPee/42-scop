#pragma once

# include "../macro.hpp"

class Camera;
class Shader;

class Draw {
	private:
		unsigned int 				_VAO, _VBO, _EBO;
		std::vector<float>			_vertices;
		std::vector<unsigned int>	_indices;
		Camera						*_camera;
		Shader						*_shader;
		glm::vec3 					_objectPosition;

		void parseObject(std::ifstream &file);
	public:
		Draw(Camera *camera, std::ifstream &file);
		~Draw();

		void drawing();
};
#pragma once

# include "../macro.hpp"

class Shader;

class Object {
	private:
		Shader						*_shader;
		std::vector<float>			_vertices;
		std::vector<unsigned int>	_indices;
		glm::vec3					_position;
		unsigned int 				_VAO, _VBO, _EBO;

		void parseFile(std::ifstream &file);
		void parsePosition();
	public:
		Object(std::ifstream &file);
		~Object();

		const glm::vec3 &getPosition() const;
		const std::vector<float> &getVertices() const;
		const std::vector<unsigned int> &getIndices() const;
		const unsigned int &getVAO() const;
		Shader *getShader() const;
};
#pragma once

# include "../macro.hpp"

class Shader;

class Object {
	private:
		Shader						*_shader;
		std::vector<float>			_vertex;
		std::vector<float>			_vertexTexture;
		std::vector<float>			_vertexNormal;
		std::vector<unsigned int>	_indice;
		std::vector<unsigned int>	_indiceTexture;
		std::vector<unsigned int>	_indiceNormal;
		glm::vec3					_position;
		unsigned int 				_VAO, _VBO, _EBO;

		void parseFile(std::ifstream &file);
		void parsePosition();
	public:
		Object(std::ifstream &file);
		~Object();

		void draw() const;

		const glm::vec3 &getPosition() const;
		void setPosition(glm::vec3 position);
		const std::vector<float> &getVertices() const;
		const std::vector<unsigned int> &getIndices() const;
		const unsigned int &getVAO() const;
		Shader *getShader() const;
};
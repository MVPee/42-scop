#pragma once

# include <iostream>
# include <string>
# include "../includes/glad/glad.h"
# include <GLFW/glfw3.h>
# include "../includes/macro.hpp"

class Window {
	private:
		GLFWwindow*	_window;
		unsigned int _shaderProgram;
		unsigned int _VAO, _VBO;

		Window(const Window &ref);
		Window &operator=(const Window &ref);
	public:
		Window();
		~Window();

		void run();

		const GLFWwindow *getWindow() const;
		bool isOpen() const;
};

std::ostream &operator<<(std::ostream &o, const Window &i);
#pragma once

# include "../macro.hpp"

class Window {
	private:
		GLFWwindow*		_window;
	public:
		Window();
		~Window();

		GLFWwindow *getWindow() const;
};

std::ostream &operator<<(std::ostream &o, const Window &i);
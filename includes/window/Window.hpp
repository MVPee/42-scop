#pragma once

# include "../macro.hpp"

class Window {
	private:
		GLFWwindow*		_window;

		Window(const Window &ref);
		Window &operator=(const Window &ref);
	public:
		Window();
		~Window();

		GLFWwindow *getWindow() const;
};

std::ostream &operator<<(std::ostream &o, const Window &i);
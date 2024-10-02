#pragma once

# include "../macro.hpp"

class KeyListener {
	private:
	public:
		KeyListener();
		~KeyListener();

		void listening(GLFWwindow *window) const;
};
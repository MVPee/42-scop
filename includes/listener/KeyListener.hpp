#pragma once

# include "../macro.hpp"

class KeyListener {
	private:
		KeyListener(const KeyListener &ref);
		KeyListener &operator=(const KeyListener &ref);
	public:
		KeyListener();
		~KeyListener();

		void listening(GLFWwindow *window) const;
};

std::ostream &operator<<(std::ostream &o, const KeyListener &i);
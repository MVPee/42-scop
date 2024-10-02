#pragma once

# include "macro.hpp"

class Window;
class KeyListener;

class Game {
	private:
		Window			*_window;
		KeyListener		*_key;
		unsigned int 	_shaderProgram;
		unsigned int 	_VAO, _VBO;

		Game(const Game &ref);
		Game &operator=(const Game &ref);
	public:
		Game();
		~Game();

		void run();

		bool isOpen() const;
};

std::ostream &operator<<(std::ostream &o, const Game &i);
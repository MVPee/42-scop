#pragma once

# include "macro.hpp"

class Window;
class KeyListener;
class Draw;

class Game {
	private:
		Window			*_window;
		KeyListener		*_key;
		Draw			*_draw;

		Game(const Game &ref);
		Game &operator=(const Game &ref);
	public:
		Game();
		~Game();

		void run();

		bool isOpen() const;
};

std::ostream &operator<<(std::ostream &o, const Game &i);
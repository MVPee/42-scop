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
	public:
		Game();
		~Game();

		void run();

		bool isOpen() const;
};
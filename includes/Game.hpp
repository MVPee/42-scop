#pragma once

# include "macro.hpp"

class Window;
class KeyListener;
class Draw;
class Camera;

class Game {
	private:
		Window			*_window;
		KeyListener		*_key;
		Draw			*_draw;
		Camera			*_camera;
	public:
		Game(std::ifstream &file);
		~Game();

		void run();

		bool isRunning() const;
};
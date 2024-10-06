#pragma once

# include "macro.hpp"

class Window;
class KeyListener;
class Camera;
class Object;

class Game {
	private:
		Window			*_window;
		KeyListener		*_key;
		Camera			*_camera;
		Object			*_object;
	public:
		Game(std::ifstream &file);
		~Game();

		void run();

		bool isRunning() const;
};
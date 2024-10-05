#pragma once

# include "../macro.hpp"

class Camera;

class KeyListener {
	private:
		Camera	*_camera;
	public:
		KeyListener(Camera *camera);
		~KeyListener();

		void listening(GLFWwindow *window) const;
};
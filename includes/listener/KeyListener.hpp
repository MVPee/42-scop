#pragma once

# include "../macro.hpp"

class Camera;

class KeyListener {
	private:
		Camera	*_camera;

		mutable bool 	_firstMouse;
		mutable float	_lastX;
		mutable float	_lastY;
	public:
		KeyListener(Camera *camera);
		~KeyListener();

		void listening(GLFWwindow *window, float deltaTime) const;
};
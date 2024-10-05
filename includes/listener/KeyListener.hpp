#pragma once

# include "../macro.hpp"

class Camera;

class KeyListener {
	private:
		Camera	*_camera;

		bool 	_firstMouse;
		float	_lastX;
		float	_lastY;
	public:
		KeyListener(Camera *camera);
		~KeyListener();

		void listening(GLFWwindow *window, float deltaTime);
		void handleMovement(GLFWwindow *window, float deltaTime);
		void handleMouseMovement(GLFWwindow *window);
};
#pragma once

# include "../macro.hpp"

class Camera {
	private:
		glm::vec3 _cameraPos; // POSITION
		glm::vec3 _cameraFront; // DIRECTION
		glm::vec3 _cameraUp; // HEIGHT
		float _yaw; // Y
		float _pitch; // X
	public:
		Camera();
		~Camera();

		void processKeyboardMovement(int direction, float deltaTime);
		void processMouseMovement(float xOffset, float yOffset);
		void updateCameraVectors();
		glm::mat4 getViewMatrix() const;
};
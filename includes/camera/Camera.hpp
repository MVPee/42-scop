#pragma once

# include "../macro.hpp"

# define TURN_AROUND false
# define FREELOOK true

class Camera {
	private:
		bool		_mode = TURN_AROUND;
		glm::vec3 	_cameraPos; // POSITION
		glm::vec3	_cameraFront; // DIRECTION
		glm::vec3 	_cameraUp; // HEIGHT
		float 		_yaw; // Y
		float 		_pitch; // X

		void updateCameraVectors();
	public:
		Camera();
		~Camera();

		void processKeyboardMovement(int direction, float deltaTime);
		void processMouseMovement(float xOffset, float yOffset);
		void reset();
		glm::mat4 getViewMatrix() const;
		const bool &getMode() const;
		void setMode(bool mode);
};
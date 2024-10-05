# include "../../includes/camera/Camera.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Camera::Camera() : _yaw(-90.0f), _pitch(0.0f) {
    _cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Camera::~Camera() {}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

/*
** ------------------------------- METHODS -----------------------------------
*/

void Camera::processKeyboard(int direction, float deltaTime) {
    float velocity = CAMERA_SPEED * deltaTime;
    if (direction == GLFW_KEY_W)
        _cameraPos += _cameraFront * velocity;
    if (direction == GLFW_KEY_S)
        _cameraPos -= _cameraFront * velocity;
    if (direction == GLFW_KEY_A)
        _cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * velocity;
    if (direction == GLFW_KEY_D)
        _cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset) {
    xOffset *= MOUSE_SPEED;
    yOffset *= MOUSE_SPEED;

    _yaw += xOffset;
    _pitch -= yOffset;

    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _cameraFront = glm::normalize(front);
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

/* ************************************************************************** */
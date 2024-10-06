# include "../../includes/camera/Camera.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Camera::Camera() {
    reset();
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

void Camera::update(Object *_object) {
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 mvp;

    //? Transform (Camera)
    if (_mode == FREELOOK)
        view = getViewMatrix();
    else {
        static float angle = 0.0f;
        angle += TURN_AROUND_SPEED;
        float camX = _object->getPosition().x + TURN_AROUND_DISTANCE * cos(angle);
        float camZ = _object->getPosition().z + TURN_AROUND_DISTANCE * sin(angle);
        float camY = _object->getPosition().y;
        view = glm::lookAt(glm::vec3(camX, camY, camZ), _object->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    projection = glm::perspective(glm::radians(45.0f), (float)(DEFAULT_WIDTH / DEFAULT_HEIGHT), 0.1f, 100.0f);
    mvp = projection * view;
    unsigned int transformLoc = glGetUniformLocation(_object->getShader()->getProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp)); 
}

void Camera::reset() {
    _yaw = -90.0f;
    _pitch = 0.0f;
    _cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _cameraFront = glm::normalize(front);

    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

    glm::vec3 cameraRight = glm::normalize(glm::cross(_cameraFront, worldUp));
    _cameraUp = glm::normalize(glm::cross(cameraRight, _cameraFront));
}


void Camera::processKeyboardMovement(int key, float deltaTime) {
    setMode(FREELOOK);
    float velocity = CAMERA_SPEED * deltaTime;
    glm::vec3 directionFront = glm::normalize(glm::vec3(_cameraFront.x, 0.0f, _cameraFront.z));
    if (key == GLFW_KEY_W)
        _cameraPos += directionFront * velocity;
    if (key == GLFW_KEY_S)
        _cameraPos -= directionFront * velocity;
    if (key == GLFW_KEY_A)
        _cameraPos -= glm::normalize(glm::cross(directionFront, _cameraUp)) * velocity;
    if (key == GLFW_KEY_D)
        _cameraPos += glm::normalize(glm::cross(directionFront, _cameraUp)) * velocity;

    if (key == GLFW_KEY_SPACE)
        _cameraPos.y += velocity;
    if (key == GLFW_KEY_LEFT_SHIFT)
        _cameraPos.y -= velocity;

    if (key == GLFW_KEY_UP)
        _pitch += CAMERA_SPEED * velocity; 
    if (key == GLFW_KEY_DOWN)
        _pitch -= CAMERA_SPEED * velocity;
    if (key == GLFW_KEY_LEFT)
        _yaw -= CAMERA_SPEED * velocity;
    if (key == GLFW_KEY_RIGHT)
        _yaw += CAMERA_SPEED * velocity;

    if (_yaw < 0.0f) _yaw += 360.0f;
    if (_yaw > 360.0f) _yaw -= 360.0f;

    updateCameraVectors();
}

void Camera::processMouseMovement(float xOffset, float yOffset) {
    xOffset *= MOUSE_SPEED;
    yOffset *= MOUSE_SPEED;

    _yaw += xOffset;
    _pitch += yOffset;

    if (_yaw < 0.0f) _yaw += 360.0f;
    if (_yaw > 360.0f) _yaw -= 360.0f;

    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _cameraFront = glm::normalize(front);

    updateCameraVectors();
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

const bool &Camera::getMode() const { return _mode; }
void Camera::setMode(bool mode) { _mode = mode; }

/* ************************************************************************** */
# include "../../includes/listener/KeyListener.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

KeyListener::KeyListener(Camera *camera) : _camera(camera) {
    _firstMouse = true;
    _lastX = 400.0f;
    _lastY = 400.0f;
}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

KeyListener::~KeyListener() {}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

/*
** ------------------------------- METHODS -----------------------------------
*/

void KeyListener::listening(GLFWwindow *window, float deltaTime) const {
    static int count = 1;
    static bool keyPressed = false;
    double xpos, ypos;

    glfwPollEvents();
    
    glfwGetCursorPos(window, &xpos, &ypos);
    if (_firstMouse) {
        _lastX = (float)xpos;
        _lastY = (float)ypos;
        _firstMouse = false;
    }
    float xOffset = xpos - _lastX;
    float yOffset = _lastY - ypos;

    _lastX = xpos;
    _lastY = ypos;
    _camera->processMouseMovement(xOffset, -yOffset);

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        _camera->processKeyboard(GLFW_KEY_W, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        _camera->processKeyboard(GLFW_KEY_S, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        _camera->processKeyboard(GLFW_KEY_A, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        _camera->processKeyboard(GLFW_KEY_D, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        if (!keyPressed) {
            if (count % 3 == 0)
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            else if (count % 3 == 1)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            count++;
            keyPressed = true;
        }
    }
    else
        keyPressed = false;
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

/* ************************************************************************** */
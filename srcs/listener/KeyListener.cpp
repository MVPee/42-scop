# include "../../includes/listener/KeyListener.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

KeyListener::KeyListener(Camera *camera) : _camera(camera){}

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

void KeyListener::listening(GLFWwindow *window) const {
    static int count = 1;
    static bool keyPressed = false;

    glfwPollEvents();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        _camera->forward();
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        _camera->backward();
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        _camera->left();
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        _camera->right();

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
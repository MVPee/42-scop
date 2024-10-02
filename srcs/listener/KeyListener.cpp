# include "../../includes/listener/KeyListener.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

KeyListener::KeyListener() {}

KeyListener::KeyListener(const KeyListener &ref) { (void)ref; }

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

KeyListener::~KeyListener() {}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

KeyListener &KeyListener::operator=(const KeyListener &ref) {
	if(this != &ref) {
		;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, const KeyListener &i) {
	(void)i;
	return o;
}

/*
** ------------------------------- METHODS -----------------------------------
*/

void KeyListener::listening(GLFWwindow *window) const {
    static int count = 1;
    static bool keyPressed = false;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        if (!keyPressed) {
            if (count % 2)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
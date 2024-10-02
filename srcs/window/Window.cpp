# include "../../includes/window/Window.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Window::Window() {
	if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	const std::string windowHeader = std::string(PROGRAM_NAME) + " " + std::string(VERSION);
    _window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, windowHeader.c_str(), nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
	glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

Window::Window(const Window &ref) { (void)ref; }

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Window::~Window() { glfwTerminate(); }

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

Window &Window::operator=(const Window &ref) {
	if(this != &ref) {
		;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, const Window &i) {
	(void)i;
	return o;
}

/*
** ------------------------------- METHODS -----------------------------------
*/

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

GLFWwindow *Window::getWindow() const { return _window; }

/* ************************************************************************** */
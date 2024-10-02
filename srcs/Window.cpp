# include "../includes/Window.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

float vertices[] = {
    // first triangle
    -1.0f, 1.0f, 0.0f, 
    1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 

    -1.0f, -1.0f, 0.0f, 
    1.0f, -1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 
}; 

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow *window) {
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

    /* .    TRIANGLE     */
    // Charger les shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Lier les shaders à un programme
    _shaderProgram = glCreateProgram();  // Changez cela
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

    // Supprimer les shaders car ils ne sont plus nécessaires
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Créer un _VAO et un _VBO pour les sommets
    glGenVertexArrays(1, &_VAO);  // Changez cela
    glGenBuffers(1, &_VBO);       // Changez cela

    // Lier le _VAO
    glBindVertexArray(_VAO);

    // Lier le _VBO et transférer les données des sommets
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Spécifier le format des sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Délier le _VBO et le _VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}


Window::Window(const Window &ref) { (void)ref; }

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Window::~Window() {
	glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteProgram(_shaderProgram);
    glfwTerminate();
}

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

void Window::run() {
	// input
	processInput(_window);

	// Rendering, Nettoyer l'écran avec une couleur (par exemple, bleu)
	glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	// Lier le _VAO et dessiner le triangle
	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

	// Traiter les événements and swap buffer
	glfwPollEvents();
	glfwSwapBuffers(_window);
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

const GLFWwindow *Window::getWindow() const { return _window; }
bool Window::isOpen() const { return !glfwWindowShouldClose(_window); }

/* ************************************************************************** */
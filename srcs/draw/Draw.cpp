# include "../../includes/draw/Draw.hpp"

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

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Draw::Draw() {}

Draw::Draw(const Draw &ref) { (void)ref; }

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Draw::~Draw() {
	glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteProgram(_shaderProgram);
}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

Draw &Draw::operator=(const Draw &ref) {
	if(this != &ref) {
		;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, const Draw &i) {
	(void)i;
	return o;
}

/*
** ------------------------------- METHODS -----------------------------------
*/

void Draw::drawing() {
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
    glDeleteShader(vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glDeleteShader(fragmentShader);
    glLinkProgram(_shaderProgram);

    // Créer un _VAO et un _VBO pour les sommets
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

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

    /* .    DRAW     */
    //Background
    glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    // Link VAO and draw the triangle
    glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

unsigned int &Draw::getShaderProgram() { return _shaderProgram; }
unsigned int &Draw::getVAO() { return _VAO; }
unsigned int &Draw::getVBO() { return _VBO; }

/* ************************************************************************** */
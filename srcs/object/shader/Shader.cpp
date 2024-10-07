# include "../../../includes/object/shader/Shader.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

const char *_vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos, 1.0f)\n;"
    "}\0";

const char *_fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Shader::Shader() {
	int success;
    char infoLog[512];


	//* Load Shader
    _vertexShader = glCreateShader(GL_VERTEX_SHADER); //! Vertex shader
    glShaderSource(_vertexShader, 1, &_vertexShaderSource, NULL);
    glCompileShader(_vertexShader);

	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //! Fragment shader
    glShaderSource(_fragmentShader, 1, &_fragmentShaderSource, NULL);
    glCompileShader(_fragmentShader);

	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    //* Link shader to a program
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _vertexShader);
    glAttachShader(_shaderProgram, _fragmentShader);
    glLinkProgram(_shaderProgram);
}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Shader::~Shader() {
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
	glDeleteProgram(_shaderProgram);
}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

/*
** ------------------------------- METHODS -----------------------------------
*/

void Shader::use() const {
	glUseProgram(_shaderProgram); //? Use this program
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

const unsigned int &Shader::getProgram() { return _shaderProgram; }

/* ************************************************************************** */
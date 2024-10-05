# include "../../includes/draw/Draw.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos, 1.0f)\n;"
    "   ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Draw::Draw(Camera *camera) : _camera(camera) {
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, -1.0f,  0.0f, 0.0f, 1.0f,   // top 

        0.5f, -0.5f, -1.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, -1.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, -1.0f,  0.0f, 0.0f, 1.0f   // top 

    };

    /* .    TRIANGLE     */
    //* Load Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); //! Vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //! Fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    //* Link shader to a program
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

    glDeleteShader(vertexShader); //! Delete vertexShader
    glDeleteShader(fragmentShader); //! Delete fragmentShader
    glUseProgram(_shaderProgram); //? Use this program


    //* summit (VBO)
    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);


    //* array (VBA)
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Draw::~Draw() {
    glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_VAO);
    glDeleteProgram(_shaderProgram);
}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

/*
** ------------------------------- METHODS -----------------------------------
*/

void Draw::drawing() {
    //? Transform (Camera)
    glm::mat4 view = _camera->getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);
    glm::mat4 mvp = projection * view;
    unsigned int transformLoc = glGetUniformLocation(_shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp)); 

    // Background
    glClearColor(2.0f, 2.0f, 2.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Draw
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

unsigned int &Draw::getShaderProgram() { return _shaderProgram; }
unsigned int &Draw::getVAO() { return _VAO; }
unsigned int &Draw::getVBO() { return _VBO; }

/* ************************************************************************** */
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

    // float vertices[] = {
    //     0.232406, -1.216630, 1.133818,  1.0f, 0.0f, 0.0f,
    //     0.232406, -0.745504, 2.843098,  0.0f, 1.0f, 0.0f,
    //     -0.227475, -0.745504, 2.843098,  0.0f, 0.0f, 1.0f,
    //     -0.227475, -1.216630, 1.133818,  1.0f, 0.0f, 0.0f,
    //     0.232407, 1.119982, 1.133819,  0.0f, 1.0f, 0.0f,
    //     0.232406, 1.119982, 1.602814,  0.0f, 0.0f, 1.0f,
    //     -0.227475, 1.119982, 1.602813,  1.0f, 0.0f, 0.0f,
    //     -0.227475, 1.119982, 1.133818,  0.0f, 1.0f, 0.0f,
    //     0.232406, -0.340316, 2.843098,  0.0f, 0.0f, 1.0f,
    //     -0.227475, -0.340316, 2.843098,  1.0f, 0.0f, 0.0f,
    //     0.232407, -0.305193, 1.133819,  0.0f, 1.0f, 0.0f,
    //     0.232407, -0.294496, 2.297937,  0.0f, 0.0f, 1.0f,
    //     -0.227475, -0.305193, 1.133818,  1.0f, 0.0f, 0.0f,
    //     -0.227475, -0.294496, 2.297937,  0.0f, 1.0f, 0.0f,
    //     0.232406, -1.222569, 1.497195,  0.0f, 0.0f, 1.0f,
    //     0.232406, -0.745504, 1.477731,  1.0f, 0.0f, 0.0f,
    //     -0.227475, -0.745504, 1.477731,  0.0f, 1.0f, 0.0f,
    //     -0.227475, -1.222569, 1.497194,  0.0f, 0.0f, 1.0f,
    //     -0.227403, -0.731178, 0.901477,  1.0f, 0.0f, 0.0f,
    //     -0.227403, -0.731178, -0.037620,  0.0f, 1.0f, 0.0f,
    //     0.223704, -0.731178, -0.037620,  0.0f, 0.0f, 1.0f,
    //     0.223704, -0.731178, 0.901477,  1.0f, 0.0f, 0.0f,
    //     -0.227403, 1.119377, 0.901477,  0.0f, 1.0f, 0.0f,
    //     -0.227403, 1.119377, -0.037620,  0.0f, 0.0f, 1.0f,
    //     0.223704, 1.119377, -0.037620,  1.0f, 0.0f, 0.0f,
    //     0.223704, 1.119377, 0.901477,  0.0f, 1.0f, 0.0f,
    //     -0.227403, -0.129772, 0.901477,  0.0f, 0.0f, 1.0f,
    //     -0.227403, 0.551492, 0.384487,  1.0f, 0.0f, 0.0f,
    //     -0.227403, 1.104268, 0.408501,  0.0f, 1.0f, 0.0f,
    //     -0.227403, 0.507336, 0.901477,  0.0f, 0.0f, 1.0f,
    //     0.223704, 0.507336, 0.901477,  1.0f, 0.0f, 0.0f,
    //     0.223704, 1.104269, 0.408501,  0.0f, 1.0f, 0.0f,
    //     0.223704, 0.551492, 0.384487,  0.0f, 0.0f, 1.0f,
    //     0.223704, -0.129772, 0.901477,  1.0f, 0.0f, 0.0f,
    //     -0.227403, 0.634134, -0.037620,  0.0f, 1.0f, 0.0f,
    //     -0.227403, -0.066768, 0.398575,  0.0f, 0.0f, 1.0f,
    //     -0.227403, -0.684649, 0.389681,  1.0f, 0.0f, 0.0f,
    //     -0.227403, -0.075523, -0.037620,  0.0f, 1.0f, 0.0f,
    //     0.223704, 0.634134, -0.037620,  0.0f, 0.0f, 1.0f,
    //     0.223704, -0.066768, 0.398575,  1.0f, 0.0f, 0.0f,
    //     0.223704, -0.684649, 0.389681,  0.0f, 1.0f, 0.0f,
    //     0.223704, -0.075523, -0.037620,  0.0f, 0.0f, 1.0f
    // };
    // unsigned int indices[] {
    //     16, 2, 3, 17,
    //     5, 8, 7, 6,
    //     29, 30, 23,
    //     9, 6, 7, 10,
    //     14, 13, 17,
    //     11, 1, 4, 13,
    //     2, 9, 10, 3,
    //     5, 12, 14, 8,
    //     12, 11, 13, 14,
    //     1, 15, 18, 4,
    //     15, 16, 17, 18,
    //     38, 42, 21, 20,
    //     33, 39, 25, 32,
    //     34, 27, 19, 22,
    //     19, 20, 21, 22,
    //     26, 25, 24, 23,
    //     26, 23, 30, 31,
    //     31, 30, 29, 32,
    //     32, 29, 28, 33,
    //     33, 28, 27, 34,
    //     24, 25, 39, 35,
    //     35, 39, 40, 36,
    //     36, 40, 41, 37,
    //     37, 41, 42, 38,
    //     26, 31, 32,
    //     37, 38, 20,
    //     21, 42, 41,
    //     12, 5, 6,
    //     25, 26, 32,
    //     22, 21, 41,
    //     8, 14, 7,
    //     28, 36, 27,
    //     10, 14, 17, 3,
    //     33, 40, 39,
    //     40, 33, 34,
    //     11, 16, 15, 1,
    //     14, 10, 7,
    //     2, 16, 12, 9,
    //     11, 12, 16,
    //     40, 34, 22, 41,
    //     12, 6, 9,
    //     18, 17, 13, 4,
    //     36, 28, 35,
    //     37, 20, 19,
    //     29, 23, 24,
    //     19, 27, 36, 37,
    //     24, 35, 28, 29
    // };

    // float vertices[] = {
    //     // positions         // colors
    //      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
    //      0.0f,  0.5f, -1.0f,  0.0f, 0.0f, 1.0f,   // top 

    //     0.5f, -0.5f, -1.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, -1.0f,  0.0f, 1.0f, 0.0f,  // bottom left
    //      0.0f,  0.5f, -1.0f,  0.0f, 0.0f, 1.0f   // top 
    // };

    float vertices[] = {
        // Positions          // Colors
        // Front face
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, // Bottom left (red)
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, // Bottom right (green)
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // Top right (blue)
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // Top left (yellow)

        // Back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, // Bottom left (magenta)
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, // Bottom right (cyan)
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Top right (white)
        -0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f  // Top left (grey)
    };

    // Indices for the cube
    unsigned int indices[] = {
        // Front face
        0, 1, 2,
        0, 2, 3,
        // Back face
        4, 5, 6,
        4, 6, 7,
        // Left face
        0, 3, 7,
        0, 7, 4,
        // Right face
        1, 5, 6,
        1, 6, 2,
        // Bottom face
        0, 1, 5,
        0, 5, 4,
        // Top face
        3, 2, 6,
        3, 6, 7
    };


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Draw::Draw(Camera *camera) : _camera(camera) {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //* array (VBA)
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //* incides (EBO)
    glGenBuffers(1, &_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnable(GL_DEPTH_TEST);

    //? DEBUG
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Draw::~Draw() {
    glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_EBO);
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
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(DEFAULT_WIDTH / DEFAULT_HEIGHT), 0.1f, 100.0f);
    glm::mat4 mvp = projection * view;
    unsigned int transformLoc = glGetUniformLocation(_shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp)); 

    // Background
    glClearColor(2.0f, 2.0f, 2.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Draw
    glBindVertexArray(_VAO); // Liez le VAO
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

unsigned int &Draw::getShaderProgram() { return _shaderProgram; }
unsigned int &Draw::getVAO() { return _VAO; }
unsigned int &Draw::getVBO() { return _VBO; }

/* ************************************************************************** */
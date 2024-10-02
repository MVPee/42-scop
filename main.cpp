#define GL_SILENCE_DEPRECATION 
# include "includes/glad/glad.h"
# include <GLFW/glfw3.h>
# include <iostream>
# include "includes/macro.hpp"

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

// Fonction callback pour ajuster la taille de la fenêtre lorsque celle-ci est redimensionnée
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
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

int main() {
    // Initialiser GLFW
    if (!glfwInit()) {
        std::cerr << "Échec de l'initialisation de GLFW" << std::endl;
        return 1;
    }

    // Spécifier la version d'OpenGL (ici 3.3) et le profil de contexte
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Créer une fenêtre GLFW
    const std::string windowHeader = std::string(PROGRAM_NAME) + " " + std::string(VERSION);
    GLFWwindow* window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, windowHeader.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Définir le contexte OpenGL pour la fenêtre
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    // Spécifier la fonction de rappel pour redimensionner la fenêtre
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Charger les shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Lier les shaders à un programme
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Supprimer les shaders car ils ne sont plus nécessaires
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Créer un VAO et un VBO pour les sommets
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Lier le VAO
    glBindVertexArray(VAO);

    // Lier le VBO et transférer les données des sommets
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Spécifier le format des sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Délier le VBO et le VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    // Boucle principale de rendu
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // Rendering, Nettoyer l'écran avec une couleur (par exemple, bleu)
        glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Lier le VAO et dessiner le triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

        // Traiter les événements and swap buffer
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    // Nettoyage et fermeture de GLFW
    glfwTerminate();
}

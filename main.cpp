#define GL_SILENCE_DEPRECATION 
#include <GLFW/glfw3.h>
#include <iostream>

// Fonction callback pour ajuster la taille de la fenêtre lorsque celle-ci est redimensionnée
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
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
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Init", nullptr, nullptr);
    if (!window) {
        std::cerr << "Échec de la création de la fenêtre GLFW" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Définir le contexte OpenGL pour la fenêtre
    glfwMakeContextCurrent(window);

    // Spécifier la fonction de rappel pour redimensionner la fenêtre
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Boucle principale de rendu
    while (!glfwWindowShouldClose(window)) {
        // Nettoyer l'écran avec une couleur (par exemple, bleu)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Échanger les tampons avant/arrière
        glfwSwapBuffers(window);

        // Traiter les événements
        glfwPollEvents();
    }

    // Nettoyage et fermeture de GLFW
    glfwTerminate();
    return 0;
}

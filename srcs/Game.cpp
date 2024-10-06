# include "../includes/Game.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Game::Game(std::ifstream &file) {
    try {
        _window = new Window();
    }
    catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
    _camera = new Camera();
    _key = new KeyListener(_camera);
    _draw = new Draw(_camera, file);

}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Game::~Game() {
    delete _camera;
    delete _draw;
    delete _key;
    delete _window;
}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

/*
** ------------------------------- METHODS -----------------------------------
*/

void Game::run() {
    static float lastFrame = 0.0f;
    static float deltaTime = 0.0f;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    _key->listening(_window->getWindow(), deltaTime);
    _draw->drawing();

	// Traiter les événements and swap buffer
    glfwSwapBuffers(_window->getWindow());
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

bool Game::isRunning() const { return !glfwWindowShouldClose(_window->getWindow()); }

/* ************************************************************************** */
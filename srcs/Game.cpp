# include "../includes/Game.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Game::Game() {
    try {
        _window = new Window();
    }
    catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
    _camera = new Camera();
    _key = new KeyListener(_camera);
    _draw = new Draw(_camera);

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
    _key->listening(_window->getWindow());
    _draw->drawing();

	// Traiter les événements and swap buffer
    glfwSwapBuffers(_window->getWindow());
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

bool Game::isOpen() const { return !glfwWindowShouldClose(_window->getWindow()); }

/* ************************************************************************** */
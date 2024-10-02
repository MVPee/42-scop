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
    _key = new KeyListener();
    _draw = new Draw();

}

Game::Game(const Game &ref) { (void)ref; }

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Game::~Game() {
    delete _window;
    delete _key;
    delete _draw;
}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

Game &Game::operator=(const Game &ref) {
	if(this != &ref) {
		;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, const Game &i) {
	(void)i;
	return o;
}

/*
** ------------------------------- METHODS -----------------------------------
*/

void Game::run() {
    _key->listening(_window->getWindow());
    _draw->drawing();

	// Traiter les événements and swap buffer
	glfwPollEvents();
	glfwSwapBuffers(_window->getWindow());
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

bool Game::isOpen() const { return !glfwWindowShouldClose(_window->getWindow()); }

/* ************************************************************************** */
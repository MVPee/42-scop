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

    try {
        _key = new KeyListener();
    }
    catch (std::exception &e) {
        delete _window;
        throw std::runtime_error(e.what());
    }

    try {
        _draw = new Draw();
    }
    catch (std::exception &e) {
        delete _window;
        delete _key;
        throw std::runtime_error(e.what());
    }
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
    //Background
	glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Lier le _VAO et dessiner le triangle
	glUseProgram(_draw->getShaderProgram());
	glBindVertexArray(_draw->getVAO());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

	// Traiter les événements and swap buffer
	glfwPollEvents();
	glfwSwapBuffers(_window->getWindow());
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

bool Game::isOpen() const { return !glfwWindowShouldClose(_window->getWindow()); }

/* ************************************************************************** */
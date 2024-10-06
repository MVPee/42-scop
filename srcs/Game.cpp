# include "../includes/Game.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

float getDeltaTime() {
    static float lastFrame = 0.0f;
    static float deltaTime = 0.0f;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return (deltaTime);
}

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
    _object = new Object(file);

}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Game::~Game() {
    delete _camera;
    delete _key;
    delete _object;
    delete _window;
}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

/*
** ------------------------------- METHODS -----------------------------------
*/

void Game::run() {
    glClearColor(2.0f, 2.0f, 2.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _key->listening(_window->getWindow(), getDeltaTime());

    _camera->updateForObject(_object);
    _object->draw();

    glfwSwapBuffers(_window->getWindow());
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

bool Game::isRunning() const { return !glfwWindowShouldClose(_window->getWindow()); }

/* ************************************************************************** */
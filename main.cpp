#define GL_SILENCE_DEPRECATION 
# include "includes/Game.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Error\nNumber(s) of argument(s)" << std::endl;
        return 1;
    }

    std::string fileName(av[1]);
    if (fileName.size() < 5 || fileName.substr(fileName.size() - 4) != ".obj") {
        std::cerr << "Error\nNot a valid file name or extension" << std::endl;
        return 1;
    }
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error\nNot a valid file" << std::endl;
        return 1;
    }

    try {
        Game game(file);
        while (game.isRunning())
            game.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

#define GL_SILENCE_DEPRECATION 
# include "includes/Game.hpp"

int main() {
    try {
        Game game;
        while (game.isOpen())
            game.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

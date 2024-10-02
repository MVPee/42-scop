#define GL_SILENCE_DEPRECATION 
# include "includes/Window.hpp"

int main() {
    try {
        Window window;
        while (window.isOpen())
            window.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

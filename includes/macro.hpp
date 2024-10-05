#pragma once

# define PROGRAM_NAME "scop"
# define VERSION "0.2"
# define DEFAULT_WIDTH 800
# define DEFAULT_HEIGHT 600
# define CAMERA_SPEED 10.0f
# define MOUSE_SPEED 0.15f

# include <iostream>
# include <string>
# include "../glad/glad.hpp"
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

# include "Game.hpp"
# include "window/Window.hpp"
# include "listener/KeyListener.hpp"
# include "draw/Draw.hpp"
# include "camera/Camera.hpp"
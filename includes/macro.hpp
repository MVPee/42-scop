#pragma once

# define PROGRAM_NAME "scop"
# define VERSION "0.6"
# define DEFAULT_WIDTH 1920
# define DEFAULT_HEIGHT 1080
# define CAMERA_SPEED 10.0f
# define MOUSE_SPEED 0.15f

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include "../glad/glad.hpp"
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <vector>

# include "Game.hpp"
# include "window/Window.hpp"
# include "listener/KeyListener.hpp"
# include "draw/Draw.hpp"
# include "draw/shader/Shader.hpp"
# include "camera/Camera.hpp"
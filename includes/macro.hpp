#pragma once

# define PROGRAM_NAME "scop"
# define VERSION "0.8"
# define DEFAULT_WIDTH 1920
# define DEFAULT_HEIGHT 1080
# define CAMERA_SPEED 10.0f
# define MOUSE_SPEED 0.15f

# define TURN_AROUND_SPEED 0.02f
# define TURN_AROUND_DISTANCE 10.0f

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
# include <limits>
# include <array>

# include "math/Math.hpp"

# include "Game.hpp"
# include "window/Window.hpp"
# include "listener/KeyListener.hpp"
# include "camera/Camera.hpp"
# include "object/Object.hpp"
# include "object/shader/Shader.hpp"
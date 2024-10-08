NAME := scop

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

UNAME_S := $(shell uname -s)

OBJS_DIR := .objs
SOURCES :=	main.cpp \
			glad/glad.cpp \
			srcs/Game.cpp \
			srcs/window/Window.cpp \
			srcs/listener/KeyListener.cpp \
			srcs/camera/Camera.cpp \
			srcs/object/Object.cpp \
			srcs/object/shader/Shader.cpp \
			srcs/math/Math.cpp

OBJECTS := $(patsubst %.cpp,$(OBJS_DIR)/%.o,$(filter %.cpp,$(SOURCES)))
DEPENDS := $(OBJECTS:.o=.d)

CXX := c++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -g #-fsanitize=address

ifeq ($(UNAME_S), Darwin)
	INCLUDES := -I/Users/mvan-pee/.brew/Cellar/glfw/3.4/include -I/Users/mvan-pee/.brew/Cellar/glm/1.0.1/include
	LDFLAGS := -L/Users/mvan-pee/.brew/Cellar/glfw/3.4/lib -L/Users/mvan-pee/.brew/Cellar/glm/1.0.1/lib -lglfw -ldl -framework OpenGL
else ifeq ($(UNAME_S), Linux)
    INCLUDES := -I/usr/include
    LDFLAGS := -L/usr/lib -lglfw -ldl -lGL
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME) $(LDFLAGS)
	@echo "\n${RED}./$(NAME)\n${NC}"

-include $(DEPENDS)

$(OBJS_DIR)/%.o: %.cpp Makefile
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	@$(RM) -rf $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME) rsrcs/42.obj

.PHONY: all clean fclean re run

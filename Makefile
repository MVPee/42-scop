NAME := scop

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

OBJS_DIR := .objs
SOURCES := main.cpp \
			srcs/glad/glad.c

OBJECTS := $(patsubst %.cpp,$(OBJS_DIR)/%.o,$(filter %.cpp,$(SOURCES))) \
           $(patsubst %.c,$(OBJS_DIR)/%.o,$(filter %.c,$(SOURCES)))
DEPENDS := $(OBJECTS:.o=.d)

CXX := c++
CC := cc
CXXFLAGS := -std=c++11 -g -fsanitize=address

INCLUDES := -I/Users/mvan-pee/.brew/Cellar/glfw/3.4/include
LDFLAGS := -L/Users/mvan-pee/.brew/Cellar/glfw/3.4/lib -lglfw -ldl -framework OpenGL

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME) $(LDFLAGS)
	@echo "\n${RED}./$(NAME)\n${NC}"

-include $(DEPENDS)

$(OBJS_DIR)/%.o: %.cpp Makefile
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -Wall -Wextra -Werror $(INCLUDES) -MMD -MP -c $< -o $@

$(OBJS_DIR)/%.o: %.c Makefile
	@mkdir -p $(@D)
	@$(CC) -Wall -Wextra -Werror $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	@$(RM) -rf $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run

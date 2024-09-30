NAME := scop

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

OBJS_DIR := .objs
SOURCES = main.cpp

OBJECTS := $(patsubst %.cpp,$(OBJS_DIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,$(OBJS_DIR)/%.d,$(SOURCES))

CXX := c++
CXXFLAGS := -std=c++11 -Wall -Werror -Wextra -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "\n${RED}./$(NAME)\n${NC}"

-include $(DEPENDS)

$(OBJS_DIR)/%.o: %.cpp Makefile
	@mkdir -p $(@D)  # Create directory if it doesn't exist
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	@$(RM) -rf $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
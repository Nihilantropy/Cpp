# Variables
NAME = PmergeMe
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRC_DIR = ./
INC_DIR = ./
OBJ_DIR = obj

# Find all .cpp files in the srcs directory
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Create a list of corresponding .o files in the obj directory
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Main rule to build the target
all: $(NAME)

# Rule to create the final target
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Rule to clean up generated files
clean:
	rm -rf $(OBJ_DIR)

# Rule to clean up and recompile
fclean: clean
	rm -f $(NAME)

# Rule to recompile everything
re: fclean all

.PHONY: all clean fclean re

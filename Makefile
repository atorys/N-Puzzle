NAME = n_puzzle

CC = clang++ -std=c++17

CFLAGS =
SFML_INCLUDE = -I $(SRC_DIR)resources/SFML-2.5.1/include
SFML_LIB = -L $(SRC_DIR)resources/SFML-2.5.1/build/lib
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = ./srcs/

UTILITY_DIR = ./utility/
UTILITY_FILES = parse.cpp\
				solve.cpp
MODELS_DIR = ./models/
MODELS_FILE = Puzzle.cpp

MAIN_FILE = main.cpp
OBJ_DIR = ./obj/

OBJS_NAME = $(UTILITY_FILES:.cpp=.o) $(MODELS_FILE:.cpp=.o) $(MAIN_FILE:.cpp=.o)
SOURCE = $(addprefix $(SRC_DIR)$(UTILITY_DIR), $(UTILITY_FILES))\
			$(addprefix $(SRC_DIR)$(MODELS_DIR), $(MODELS_FILE))\
			$(addprefix $(SRC_DIR), $(MAIN_FILE))
OBJS = 		$(addprefix $(OBJ_DIR), $(OBJS_NAME))

SO_LONG_OBJ = $(addprefix $(OBJ_DIR), $(SO_LONG_OBJ_FILES))

VPATH = ./srcs/ \
		./srcs/algorithm/\
		./srcs/graphics/\
		./srcs/models/\
		./srcs/utility/

HEADER = ./srcs/algorithm/Heuristics.hpp\
			./srcs/algorithm/SearchAlgorithm.hpp\
			./srcs/graphics/Assets.hpp\
			./srcs/graphics/Graphics.hpp\
			./srcs/graphics/Visualizer.hpp\
			./srcs/models/Puzzle.hpp\
			./srcs/utility/utility.hpp

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
		sudo $(CC) $(OBJS) $(SFML_LIB) -o $(NAME) $(SFML_FLAGS)

$(OBJS): $(HEADER)
			mkdir -p $(OBJ_DIR)
			$(CC) -I $(HEADER) -c $(SOURCE) $(SFML_INCLUDE)
			mv $(OBJS_NAME) $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

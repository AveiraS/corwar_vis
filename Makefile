NAME = corewar
CC = gcc
FLAGS = -g -Wall -Wextra -Werror
HEAD_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_HEAD = $(LIBFT_DIR)/include
HEAD_FILES = corewar.h op.h
VIS_FOLDER = visualizator
SRC_FILES = main.c error.c input.c arena.c battle.c delete.c op1.c op2.c op3.c op4.c output.c players.c process.c table.c
SRC_VIS = 	$(VIS_FOLDER)/choose_colors_pt1.c \
			$(VIS_FOLDER)/choose_colors_pt2.c \
			$(VIS_FOLDER)/push_info.c \
			$(VIS_FOLDER)/visualizator.c \
			$(VIS_FOLDER)/visualizator_help.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
INCLUDE_FOLDER = include/

FRAMEWORKS = -lSDL2 -lSDL2_ttf -LSDL2_image -lSDL
#FRAMEWORKS =	-I/Library/Frameworks/SDL2.framework/Headers -F ~/Library/Frameworks -framework SDL2 \
			-I/Library/Frameworks/SDL2_ttf.framework/Headers -F ~/Library/Frameworks -framework SDL2_ttf

all: $(NAME)

-include $(OBJ:.o=.d)

$(NAME): $(LIBFT)
#	@bash $(VIS_FOLDER)/script.bash
	@gcc $(FLAGS) $(SRC) $(SRC_VIS) $(FRAMEWORKS) $(LIBFT) -I $(INCLUDE_FOLDER) -I $(LIBFT_HEAD) -o $(NAME)

# $(NAME): $(OBJ) $(LIBFT)
	# $(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	# $(CC) $(FLAGS) -I $(HEAD_DIR) -I $(LIBFT_HEAD) $(FRAMEWORK) -o $@ -c $< -MMD

# $(OBJ_DIR):
	# mkdir -p $(OBJ_DIR)

$(LIBFT): FAKE
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re FAKE

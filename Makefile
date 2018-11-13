SRC_GAME_NAME = main.c

SRC_EDITOR_NAME = main.c

NAME_GAME = doom-nukem
NAME_EDITOR = editor

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -framework OpenGL -framework AppKit
MLX = minilibx_macos/libmlx.a 
LIBFT = libft/libft.a
INC = -I libft/

OBJ_GAME_PATH = obj/game/
OBJ_EDITOR_PATH = obj/editor/

OBJ_GAME_NAME = $(SRC_GAME_NAME:.c=.o)
OBJ_EDITOR_NAME = $(SRC_EDITOR_NAME:.c=.o)

SRC_GAME_PATH = srcs/game/
SRC_EDITOR_PATH = srcs/editor/

SRC_GAME = $(addprefix $(SRC_GAME_PATH),$(SRC_GAME_NAME))
SRC_EDITOR = $(addprefix $(SRC_EDITOR_PATH),$(SRC_EDITOR_NAME))

OBJ_GAME = $(addprefix $(OBJ_GAME_PATH),$(OBJ_GAME_NAME))
OBJ_EDITOR = $(addprefix $(OBJ_EDITOR_PATH),$(OBJ_EDITOR_NAME))

all : $(NAME_GAME) $(NAME_EDITOR)

$(NAME_GAME) : $(LIBFT) $(MLX) $(OBJ_GAME_PATH) $(OBJ_GAME)
	@echo ""
	@$(CC) -o $(NAME_GAME) $(OBJ_GAME) $(LFLAGS)
	@echo "\x1b[32;01m$(NAME_GAME) SUCCESSFULLY CREATED !\x1b[32;00m"

$(NAME_EDITOR) : $(LIBFT) $(MLX) $(OBJ_EDITOR_PATH) $(OBJ_EDITOR)
	@echo ""
	@$(CC) -o $(NAME_EDITOR) $(OBJ_EDITOR) $(LFLAGS)
	@echo "\x1b[32;01m$(NAME_EDITOR) SUCCESSFULLY CREATED !\x1b[32;00m"

$(OBJ_GAME_PATH):
	mkdir -p $(OBJ_GAME_PATH)

$(OBJ_EDITOR_PATH):
	mkdir -p $(OBJ_EDITOR_PATH)


$(OBJ_GAME_PATH)%.o: $(SRC_GAME_PATH)%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJ_EDITOR_PATH)%.o: $(SRC_EDITOR_PATH)%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(LIBFT) :
	@make -C libft/
	@make -C minilibx_macos/
	@echo "\033[32mLibrairies compiled\033[0m"

$(MLX) :
	@make -C minilibx_macos/

.PHONY : all clean fclean re

clean :
	@rm -rf obj/
	@make -C libft/ clean
	@make -C minilibx_macos/ clean
	@echo "\033[32mObjects deleted\nLibraries cleaned\033[0m"

fclean : clean
	@make -C libft/ fclean
	@rm -rf $(NAME_EDITOR)
	@rm -rf $(NAME_GAME)
	@echo "\033[32m$(NAME) deleted\033[0m"

re : fclean all

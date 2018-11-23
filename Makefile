SRC_EDITOR_NAME =	main.c \
					loop_hook.c \
					mouse_hook.c \
					key_hook.c \
					polygon.c \
					mlx_img_func.c \
					bresenham.c \
					bresenham_quadrants.c \
					segment.c \
					tools.c \
					intersection.c \
					draw_edge.c \
					maths_tools.c \
					debug.c \
					edge_tools.c \
					parser_tga.c \
					editor_interactions.c

SRC_GAME_NAME =		main.c \
					print_memory.c

NAME_GAME = doom-nukem
NAME_EDITOR = editor

CC = gcc

# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -g -fsanitize=address

MLX = minilibx_macos/libmlx.a 
LIBFT = libft/libft.a
LFLAGS = -framework OpenGL -framework AppKit $(LIBFT) $(MLX) -fsanitize=address
INC = -I libft/ -I includes/ -I minilibx_macos/

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
	@$(CC) $(OBJ_GAME) $(LFLAGS) -o $@ 
	@echo "\x1b[32;01m$@ SUCCESSFULLY CREATED !\x1b[32;00m"

$(NAME_EDITOR) : $(LIBFT) $(MLX) $(OBJ_EDITOR_PATH) $(OBJ_EDITOR)
	@echo ""
	@$(CC) $(OBJ_EDITOR) $(LFLAGS) -o $@ 
	@echo "\x1b[32;01m$@ SUCCESSFULLY CREATED !\x1b[32;00m"

$(OBJ_GAME_PATH):
	@mkdir -p $@

$(OBJ_EDITOR_PATH):
	@mkdir -p $@


$(OBJ_GAME_PATH)%.o: $(SRC_GAME_PATH)%.c
	@echo "\x1b[32;01m.\x1b[32;00m\c"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJ_EDITOR_PATH)%.o: $(SRC_EDITOR_PATH)%.c
	@echo "\x1b[32;01m.\x1b[32;00m\c"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(LIBFT) :
	@make -C libft/
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
	@echo "\033[32m$(NAME_EDITOR) deleted\033[0m"
	@echo "\033[32m$(NAME_GAME) deleted\033[0m"

fake_clean :
	@rm -rf obj/

re : fclean all

make fake_re :  fake_clean all

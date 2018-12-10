SRC_EDITOR_NAME =	 \
					png/filter.c \
					png/filter_2.c \
					png/globals_inflate.c \
					png/huffman_get_code_from_length.c \
					png/inflate.c \
					png/inflate_2.c \
					png/resize.c \
					png/parser.c \
					png/parser_2.c \
					png/tree.c \
						\
					main.c \
					loop_hook.c \
					mouse_hook.c \
					key_hook.c \
					polygon.c \
					mlx_img_func.c \
					bresenham.c \
					bresenham_quadrants.c \
					intersect_two_segments.c \
					tools.c \
					intersection.c \
					create_edge.c \
					maths_tools.c \
					imaths.c \
					debug.c \
					edge_tools.c \
					parser_tga.c \
					editor_interactions.c \
					delete.c \
					binary_tools.c \
					print_memory.c \
					file_listing.c \
					calculate_file_size.c \
					save_scene.c

SRC_GAME_NAME =		main.c \
					print_memory.c

NAME_GAME = doom-nukem
NAME_EDITOR = editor

CC = gcc

# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -g -fsanitize=address

MLX = minilibx_macos/libmlx.a 
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a
LFLAGS = -framework OpenGL -framework AppKit $(LIBFT) $(FT_PRINTF) $(MLX) -fsanitize=address
INC = -I libft/ -I includes/ -I minilibx_macos/ -I ft_printf/includes

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

$(NAME_GAME) : $(LIBFT) $(FT_PRINTF) $(MLX) $(OBJ_GAME_PATH) $(OBJ_GAME)
	@echo ""
	@$(CC) $(OBJ_GAME) $(LFLAGS) -o $@ 
	@echo "\x1b[32;01m$@ SUCCESSFULLY CREATED !\x1b[32;00m"

$(NAME_EDITOR) : $(LIBFT) $(FT_PRINTF) $(MLX) $(OBJ_EDITOR_PATH) $(OBJ_EDITOR)
	@echo ""
	@$(CC) $(OBJ_EDITOR) $(LFLAGS) -o $@ 
	@echo "\x1b[32;01m$@ SUCCESSFULLY CREATED !\x1b[32;00m"

$(OBJ_GAME_PATH):
	@mkdir -p $@

$(OBJ_EDITOR_PATH):
	@mkdir -p $@
	@mkdir -p $@/png


$(OBJ_GAME_PATH)%.o: $(SRC_GAME_PATH)%.c
	@echo "\x1b[32;01m.\x1b[32;00m\c"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJ_EDITOR_PATH)%.o: $(SRC_EDITOR_PATH)%.c
	@echo "\x1b[32;01m.\x1b[32;00m\c"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(LIBFT) :
	@make -C libft/
	@echo "\033[32mLibrairies compiled\033[0m"

$(FT_PRINTF) :
	@make -C ft_printf/
	@echo "\033[32mLibrairies compiled\033[0m"

$(MLX) :
	@make -C minilibx_macos/

.PHONY : all clean fclean re

clean :
	@rm -rf obj/
	@make -C libft/ clean
	@make -C ft_printf/ clean
	@make -C minilibx_macos/ clean
	@echo "\033[32mObjects deleted\nLibraries cleaned\033[0m"

fclean : clean
	@make -C libft/ fclean
	@make -C ft_printf/ fclean
	@rm -rf $(NAME_EDITOR)
	@rm -rf $(NAME_GAME)
	@echo "\033[32m$(NAME_EDITOR) deleted\033[0m"
	@echo "\033[32m$(NAME_GAME) deleted\033[0m"

fake_clean :
	@rm -rf obj/

re : fclean all

make fake_re :  fake_clean all

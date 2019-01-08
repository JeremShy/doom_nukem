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
					editor_interactions.c \
					delete.c \
					binary_tools.c \
					print_memory.c \
					file_listing.c \
					calculate_file_size.c \
					calculate_nbs.c \
					fill_hash_maps.c \
					get_polygon_from_point.c \
					add_stuff.c \
					find_next_sectors.c \
					save_scene.c 

SRC_GAME_NAME =		parsing/parse_map.c \
					parsing/simple_parse.c \
					parsing/sector.c \
					\
					bresenham.c \
					bresenham_quadrants.c \
					fill_printed_edges.c \
					cmp_edges_order.c \
					intersect_edges.c \
					handle_key_events.c \
					key_hook.c \
					log.c \
					main.c \
					mlx_loop.c \
					mlx_img_func.c \
					mouse_hook.c \
					points_angle.c \
					print_wall.c \
					projection_point.c \

NAME_GAME = doom-nukem
NAME_EDITOR = editor

CC = gcc

# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -g -fsanitize=address

LIB_PATH = libsrcs/

MLX = $(LIB_PATH)minilibx_macos/libmlx.a 
LIBFT = $(LIB_PATH)libft/libft.a
FT_PRINTF = $(LIB_PATH)ft_printf/libftprintf.a
FT_MATRIX = $(LIB_PATH)libftmatrices/libftmatrices.a
FT_DOOM = $(LIB_PATH)libdoom/libdoom.a

LFLAGS = -framework OpenGL -framework AppKit $(LIBFT) $(FT_PRINTF) $(MLX) $(FT_MATRIX) $(FT_DOOM) -fsanitize=address
INC = -I $(LIB_PATH)libft/ -I includes/ -I $(LIB_PATH)minilibx_macos/ -I $(LIB_PATH)ft_printf/includes -I $(LIB_PATH)libftmatrices/includes -I $(LIB_PATH)libdoom/includes

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

$(NAME_GAME) : $(LIBFT) $(FT_PRINTF) $(FT_MATRIX) $(MLX) $(FT_DOOM) $(OBJ_GAME_PATH) $(OBJ_GAME)
	@echo ""
	@$(CC) $(OBJ_GAME) $(LFLAGS) -o $@ 
	@echo "\x1b[32;01m$@ SUCCESSFULLY CREATED !\x1b[32;00m"

$(NAME_EDITOR) : $(LIBFT) $(FT_PRINTF) $(MLX) $(OBJ_EDITOR_PATH) $(OBJ_EDITOR)
	@echo ""
	@$(CC) $(OBJ_EDITOR) $(LFLAGS) -o $@ 
	@echo "\x1b[32;01m$@ SUCCESSFULLY CREATED !\x1b[32;00m"

$(OBJ_GAME_PATH):
	@mkdir -p $@
	@mkdir -p $@/parsing

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
	@make -C $(LIB_PATH)libft/
	@echo "\033[32mlibft compiled\033[0m"

$(FT_MATRIX) :
	@make -C $(LIB_PATH)libftmatrices/
	@echo "\033[32mft_matrix compiled\033[0m"

$(FT_PRINTF) :
	@make -C $(LIB_PATH)ft_printf/
	@echo "\033[32mft_printf compiled\033[0m"

$(FT_DOOM) :
	@make -C $(LIB_PATH)libdoom/
	@echo "\033[32mlib_doom compiled\033[0m"

$(MLX) :
	@make -C $(LIB_PATH)minilibx_macos/
	@echo "\033[32mMlx compiled\033[0m"

.PHONY : all clean fclean re

clean :
	@rm -rf obj/
	@make -C $(LIB_PATH)libft/ clean
	@make -C $(LIB_PATH)ft_printf/ clean
	@make -C $(LIB_PATH)libftmatrices/ clean
	@make -C $(LIB_PATH)minilibx_macos/ clean
	@make -C $(LIB_PATH)libdoom/ clean
	@echo "\033[32mObjects deleted\nLibraries cleaned\033[0m"

fclean : clean
	@make -C $(LIB_PATH)libft/ fclean
	@make -C $(LIB_PATH)ft_printf/ fclean
	@make -C $(LIB_PATH)libftmatrices/ fclean
	@make -C $(LIB_PATH)libdoom/ fclean
	@rm -rf $(NAME_EDITOR)
	@rm -rf $(NAME_GAME)
	@echo "\033[32m$(NAME_EDITOR) deleted\033[0m"
	@echo "\033[32m$(NAME_GAME) deleted\033[0m"

fake_clean :
	@rm -rf obj/

re : fclean all

make fake_re :  fake_clean all


SRC_PATH = ./srcs/

SRC_NAME = maths_tools.c

OBJ_PATH = ./obj/

LIB_PATH = ./

NAME = ./libdoom.a

CC = gcc

CFLAGS = -Werror -Wall -Wextra -c -g

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix -L,$(LIB_PATH))
INC = -Iincludes -I../../includes -I../libftmatrices/includes -I../libft

all: $(NAME)

$(NAME): $(OBJ)
	@ar r $(NAME) $(OBJ) >&- 2>&-
	@echo ""
	@ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@echo "\x1b[32;01m.\x1b[32;00m\c"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<


clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: libft minilibx

SRCS = map.c \
	   read.c \
	   player.c \
	   coord.c \
	   raycast.c \
	   raydraw.c \
	   raysprite.c \
	   setup_mlx.c \
	   draw.c \
	   texture.c \
	   keyboard.c \
	   sprite.c \
	   hook.c \
	   main.c

NAME = wolf3d
GCC_FLAG = -Wall -Werror -Wextra -g
CC = gcc $(GCC_FLAG)

OBJS = $(SRCS:.c=.o)

all: libft minilibx $(NAME)

libft:
	make -C ./libft/

minilibx:
	make -C ./minilibx/

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -Lminilibx/ -lmlx -framework OPENGL -framework Appkit -Llibft -lft

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx/ clean

re: fclean all

NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux

MLX = -L./minilibx-linux -lmlx -lX11 -lXext -lbsd

SRC = srcs/main.c srcs/map.c srcs/object.c srcs/player.c

OBJ = $(SRC:.c=.o)


# Regla para crear el ejecutable


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX)

# Regla para compilar los archivos fuente en objetos

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar archivos objeto
clean:

	rm -f $(OBJ)

# Regla para limpiar los objetos y el ejecutable
fclean: clean
	rm -f $(NAME)

# Regla para recompilar todo
re: fclean $(NAME)

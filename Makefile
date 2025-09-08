NAME = so_long

CC = cc

CFLAGS = -g -Wall -Wextra -Werror -I./minilibx-linux

MLX = -L./minilibx-linux -lmlx -lX11 -lXext -lbsd

SRC = srcs/get_next_line_utils.c srcs/get_next_line.c srcs/main.c srcs/map_checking.c srcs/map_reading.c srcs/map_valid_way_flood_fill.c srcs/map_valid_way_rectangular.c srcs/map.c srcs/object.c srcs/player.c srcs/utils.c 

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

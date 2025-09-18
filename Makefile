NAME = so_long

CC = cc

CFLAGS = -g -Wall -Wextra -Werror -I minilibx-linux

MLX = -Lminilibx-linux -lmlx -lX11 -lXext -lbsd

SRC = srcs/get_next_line_utils.c srcs/get_next_line.c srcs/main.c srcs/map_checking.c srcs/map_reading.c srcs/map_valid_way_flood_fill.c srcs/map_valid_way_rectangular.c srcs/utils.c 

OBJ = $(SRC:.c=.o)

# Regla principal: Compilar el proyecto, primero asegurándonos de que MiniLibX esté compilada
$(NAME): $(OBJ) libmlx
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX)

# Regla para compilar los archivos fuente en objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
	make clean

# Regla para limpiar archivos objeto
clean:
	rm -f $(OBJ)

# Regla para limpiar los objetos, el ejecutable y la librería
fclean: clean
	rm -f $(NAME)
	rm -f libmlx/libmlx.a

# Regla para recompilar todo
re: fclean $(NAME)

# Regla para compilar MiniLibX
libmlx:
	@echo "Compilando MiniLibX..."
	@make -C minilibx-linux
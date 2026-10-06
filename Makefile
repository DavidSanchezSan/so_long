# Nombre del ejecutable:
NAME = so_long

# Compilador y flags:
CC = cc
CFLAGS = -Wall -Wextra -Werror -I minilibx-linux

# Librerías externas:
MLX = -Lminilibx-linux -lmlx -lX11 -lXext -lbsd

# Archivos fuente:
SRC =	srcs/get_next_line_cleaner.c \
		srcs/get_next_line_utils.c \
		srcs/get_next_line.c \
		srcs/images_management.c \
		srcs/main.c \
		srcs/map_checking.c \
		srcs/map_reading.c \
		srcs/map_valid_way_flood_fill.c \
		srcs/map_valid_way_rectangular.c \
		srcs/movement.c \
		srcs/utils_2.c \
		srcs/utils.c \
		srcs/ft_printf.c \
		srcs/put_char_nbr_digit.c \
		srcs/put_str_hex_ptr.c \

# Archivos objeto:
OBJ = $(SRC:.c=.o)

# Regla por defecto:
all: $(NAME)

# Regla principal: Compilar el proyecto
$(NAME): $(OBJ) libmlx
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX)

# Regla para compilar .c a .o:
%.o: %.c so_long.h
	@$(CC) $(CFLAGS) -c $< -o $@

# # Target de test:
# test: $(NAME)
# 	@echo "Ejecutando programa de prueba..."
# 	make clean

# Regla para limpiar archivos objeto
clean:
	@rm -f $(OBJ)

# Regla para limpiar los objetos, el ejecutable y la librería
fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx/libmlx.a

# Regla para recompilar todo
re: fclean all

# Regla para compilar MiniLibX
libmlx:
	@echo "Compilando MiniLibX..."
	@make -C minilibx-linux
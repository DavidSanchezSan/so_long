/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:31:52 by dasanche          #+#    #+#             */
/*   Updated: 2025/08/28 18:54:22 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include "mlx.h"

# define BUFFER_SIZE 64
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define CELL_SIZE 64
# define MAP_WIDTH 10
# define MAP_HEIGHT 8

// Estructura para gestionar el estado del juego
typedef struct s_game
{
	void	*mlx; // Conexión con la biblioteca mlx
	void	*win; // Ventana del juego
	char	**map; // Mapa del juego
	int		player_x; // Posición X del jugador
	int		player_y; // Posición Y del jugador
}	t_game;

// Estructura para el mapa:
typedef struct s_map
{
	int	x; // Eje x (columnas)
	int	y; // Eje y (Filas)
	int	objects; // Objetos
	int	exits; // Salidas
	int	initial_pos;
}	t_map;

int		key_hook(int keycode, void *param);
int		close_game(t_game *game);
// void	move_player(t_game *game, int dx, int dy);
// char	get_map_cell(int x, int y);
// void	draw_map(t_game *game);
//
int		valid_walls(char **map, int width, int height);
int		valid_chars(char **map, int width, int height);
int		exit_init_pos_count(char **map, int width, int height);
int		exit_count(char **map, int width, int height);
void	get_map_dimensions(char **map, int *width, int *height);
int		map_checks(char **map);
int		ber_extension_validation(char *name_map);
void	print_error(char *msg);
char	*ft_strrchr(char *s, int c);
//gnl
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);

char	*get_next_line(int fd);

int		open_file(char *filename);
// char	**resize_map(int lines_allocated);
char	**read_map(char *filename);
// char	**get_map(int fd, int *lines_allocated, char **map);
void	free_map(char **map);

int		rectangular_map(char **map, int width, int height);
#endif
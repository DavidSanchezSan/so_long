/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:31:52 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/16 16:05:36 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 64
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// Coordenadas:
typedef struct s_coord
{
	int		x;
	int		y;
}			t_coord;

// Estructura para el mapa:
typedef struct s_map
{
	char	**map;
	int		x;               // Eje x (columnas)
	int		y;               // Eje y (Filas)
	int		objects;         // Objetos
	int		exits;           // Salidas
	t_coord	initial_pos; // Posición inicial
}			t_map;

// Stack para revisar el mapa en flood/fill
// Con coordenadas y top
typedef struct s_stack
{
	t_coord	*arr;
	int		top;
}			t_stack;

// Estructura para pasar un conjunto de parametros a flood fill:
typedef struct s_ff_params
{
	t_map	*data_map;
	int		width;
	int		height;
	int		reach_c;
	int		reach_e;
	void	*mlx;
	void	*mlx_win;
}			t_ff_params;

// main
t_ff_params	*init_game(t_ff_params *game);
void		free_map_structs(t_ff_params *game);
// gnl + gnl_utils
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*get_next_line(int fd);
// map_checking
int			valid_chars(char **map, int width, int height);
int			valid_walls(char **map, int width, int height);
int			exit_init_pos_count(char **map, int width, int height);
void		obj_count(t_ff_params *game);
int			map_checks(t_ff_params *game);
// map_reading
void		get_map_dimensions(char **map, int *width, int *height);
char		**read_map(char *filename, t_ff_params *game);
// map_valid_way_flood_fill
void		flood_fill(t_ff_params *p, int start_x, int start_y);
// map_valid_way_rectangular
int			rectangular_map(char **map, int width, int height);
char		**dup_map(char **map);
int			find_player(char **map, int *px, int *py);
int			valid_path(t_ff_params *game);
// utils
void		print_error(char *msg);
char		*ft_strrchr(char *s, int c);
int			ber_extension_validation(char *name_map);
int			open_file(char *filename);
void		free_map(char **map);
#endif
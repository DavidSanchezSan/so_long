/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:31:52 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:56 by dasanche         ###   ########.fr       */
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

// Coordenadas:
typedef struct s_coord
{
	int			x;
	int			y;
}				t_coord;

// Estructura para el mapa:
typedef struct s_map
{
	char		**map;
	int			x;
	int			y;
	int			objects;
	int			exits;
	t_coord		exit_pos;
	t_coord		initial_pos;
}				t_map;

// Stack para revisar el mapa en flood/fill
// Con coordenadas y top
typedef struct s_stack
{
	t_coord		*arr;
	int			top;
}				t_stack;

// Estructura para pasar un conjunto de parametros a flood fill:
typedef struct s_ff_params
{
	t_map		*data_map;
	int			width;
	int			height;
	int			reach_c;
	int			reach_e;
	int			steps;

	void		*mlx;
	void		*mlx_win;
	int			tile_size;

	void		*image_wall;
	void		*image_floor;
	void		*image_player;
	void		*image_collectible;
	void		*image_exit;
}				t_ff_params;
// get_next_line_cleaner
char			*ft_cleanup_stored(char **stored, char *line);
// main
void			print_map(t_ff_params *game);
void			free_map_structs(t_ff_params *game);
t_map			*init_map(t_map *data_map);
t_ff_params		*init_game(t_ff_params *game);
int				close_window(t_ff_params *game);
int				key_handler(int keycode, t_ff_params *game);
void			move_player(t_ff_params *game, int x, int y);
void			*load_image(const char *filename, int *image_width,
					t_ff_params *game);
void			init_images(t_ff_params *game);
void			render_map(t_ff_params *game, char **map);
// gnl + gnl_utils
char			*ft_strdup(const char *s);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*get_next_line(int fd);
// map_checking
int				valid_chars(char **map, int width, int height);
int				valid_walls(char **map, int width, int height);
int				exit_init_pos_count(char **map, int width, int height);
void			obj_count(t_ff_params *game);
int				map_checks(t_ff_params *game);
// map_reading
void			get_map_dimensions(char **map, int *width, int *height);
char			**read_map(char *filename, t_ff_params *game);
// map_valid_way_flood_fill
void			flood_fill(t_ff_params *p, int start_x, int start_y);
// map_valid_way_rectangular
int				rectangular_map(char **map, int width, int height);
char			**dup_map(char **map);
int				find_player(char **map, int *px, int *py);
int				valid_path(t_ff_params *game);
// utils
void			print_error(char *msg);
char			*ft_strrchr(char *s, int c);
int				ber_extension_validation(char *name_map);
int				open_file(char *filename);
void			free_map(char **map);
int				free_error_print(char *msg, t_ff_params *game, int ret);
void			finish_game(t_ff_params *game);
int				parsing_map(int argc, char **argv, t_ff_params *game);
// Printf
int				ft_printf(char const *str, ...);
int				ft_putchar_int_fd(char c, int fd);
void			ft_one_digit(int *count, int fd, int n);
void			ft_one_unsigned_digit(unsigned int *count, int fd, int n);
int				ft_putnbr_int_fd(int n, int fd);
unsigned int	ft_putnbr_unint_fd(unsigned int n, int fd);
int				ft_putstr_int_fd(char *s, int fd);
int				ft_hex_low_fd(unsigned long n, int fd);
int				ft_hex_upp_fd(unsigned long n, int fd);
int				ft_ptr_fd(void *ptr, int fd);
#endif
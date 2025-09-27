/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:36:58 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:45 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Función que carga las imágenes en memoria:
void	*load_image(const char *filename, int *image_width, t_ff_params *game)
{
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, (char *)filename, image_width,
			image_width);
	if (!img)
	{
		ft_printf("Error al cargar la imagen XPM\n");
		exit(1);
	}
	return (img);
}

//Función que carga las imágenes concretas usando la función anterior:
void	init_images(t_ff_params *game)
{
	game->image_wall = load_image("srcs/images/Tree_01.xpm", &game->tile_size,
			game);
	game->image_floor = load_image("srcs/images/Grass_01.xpm", &game->tile_size,
			game);
	game->image_player = load_image("srcs/images/Marceline_01.xpm",
			&game->tile_size, game);
	game->image_collectible = load_image("srcs/images/Bass_01.xpm",
			&game->tile_size, game);
	game->image_exit = load_image("srcs/images/Portal_01.xpm", &game->tile_size,
			game);
}

//Función que dibuja/pone la imagen en función del caracter:
void	manage_image(t_ff_params *game, char **map, int x, int i)
{
	if (map[i][x] == '0')
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->image_floor, x
			* game->tile_size, i * game->tile_size);
	if (map[i][x] == '1')
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->image_wall, x
			* game->tile_size, i * game->tile_size);
	if (map[i][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->image_player, x
			* game->tile_size, i * game->tile_size);
	if (map[i][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->image_collectible, x * game->tile_size, i * game->tile_size);
	if (map[i][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->image_exit, x
			* game->tile_size, i * game->tile_size);
}

//Función para el renderizado del mapa:
void	render_map(t_ff_params *game, char **map)
{
	int	i;
	int	x;

	i = 0;
	while (map[i])
	{
		x = 0;
		while (map[i][x])
		{
			manage_image(game, map, x, i);
			x++;
		}
		i++;
	}
}

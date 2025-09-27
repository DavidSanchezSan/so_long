/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:07:19 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:48 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Todos los caracteres son válidos:
int	valid_chars(char **map, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	while (x < height)
	{
		y = 0;
		while (y < width)
		{
			if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != 'C'
				&& map[x][y] != 'E' && map[x][y] != 'P')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

// Todo el mapa rodeado de muros:
int	valid_walls(char **map, int width, int height)
{
	int	x;

	x = 0;
	while (x < width)
	{
		if (map[0][x] != '1' || map[height - 1][x] != '1')
			return (0);
		x++;
	}
	x = 0;
	while (x < height)
	{
		if (map[x][0] != '1' || map[x][width - 1] != '1')
			return (0);
		x++;
	}
	return (1);
}

// Conteo de salida/objetos/posición_inicial:
int	exit_init_pos_count(char **map, int width, int height)
{
	int	x;
	int	y;
	int	exit_count;
	int	init_pos_count;

	y = 0;
	exit_count = 0;
	init_pos_count = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'E')
				exit_count++;
			else if (map[y][x] == 'P')
				init_pos_count++;
			x++;
		}
		y++;
	}
	if (exit_count != 1 || init_pos_count != 1)
		return (print_error("Map needs 1 E, 1 P, and at least 1 C\n"), 0);
	return (1);
}

// Conteo de objetos:
void	obj_count(t_ff_params *game)
{
	int	x;
	int	y;

	y = 0;
	game->data_map->objects = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->data_map->map[y][x] == 'C')
				game->data_map->objects++;
			x++;
		}
		y++;
	}
}

// Chequeos del mapa:
int	map_checks(t_ff_params *game)
{
	get_map_dimensions(game->data_map->map, &game->width, &game->height);
	if (rectangular_map(game->data_map->map, game->width, game->height) != 1)
		return (print_error("Map must be rectangular only\n"), 0);
	if (!valid_walls(game->data_map->map, game->width, game->height)
		|| !valid_chars(game->data_map->map, game->width, game->height))
		return (print_error("Map not enclosed by walls or has invalid chars\n"),
			0);
	if (exit_init_pos_count(game->data_map->map, game->width,
			game->height) == 0)
		return (0);
	obj_count(game);
	if (game->data_map->objects == 0)
		return (print_error("Map has no objects\n"), (0));
	if (!valid_path(game))
		return (0);
	return (1);
}

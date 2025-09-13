/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:07:19 by dasanche          #+#    #+#             */
/*   Updated: 2025/08/28 16:54:21 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Todos los caracteres son válidos:
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

//Todo el mapa rodeado de muros:
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
		if (map[x][0] != '1' || map[x][width -1] != '1')
			return (0);
		x++;
	}
	return (1);
}

//Conteo de salida/objetos/posición_inicial:

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
		return (print_error("Map needs 1 E, 1 P, and at least 1 C\n"),
			0);
	return (1);
}

// Conteo de objetos:
int	obj_count(char **map, int width, int height)
{
	int	x;
	int	y;
	int	obj_count;

	y = 0;
	obj_count = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'C')
				obj_count++;
			x++;
		}
		y++;
	}
	return (obj_count);
}

//Chequeos del mapa:
int	map_checks(char **map)
{
	int	width;
	int	height;
	int	objects;

	get_map_dimensions(map, &width, &height);
	if (rectangular_map(map, width, height) != 1)
		return (print_error("Map must be rectangular only\n"), 0);
	if (!valid_walls(map, width, height) || !valid_chars(map, width, height))
		return (print_error("Map not enclosed by walls or has invalid chars\n"),
			0);
	if (exit_init_pos_count(map, width, height) == 0)
		return (0);
	objects = obj_count(map, width, height);
	if (objects == 0)
		return(print_error("Map has no objects\n"), (0));
	if (!valid_path(map, objects))
		return (0);
	return (objects);
}

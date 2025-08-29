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

// Todos los caracteres son validos:
int	valid_characters(char **map, int width, int height)
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

// Todos el mapa esta rodeado de muros:
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
// Conteo de salida/objeto/posicion_inicial:

int obj_exit_init_pos_count(char **map, int width, int height)
{
    int	x;
	int	y;
    int exit_count;
    int obj_count;
    int init_pos_count;

    y = 0;
	exit_count = 0;
	obj_count = 0;
	init_pos_count = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            if (map[y][x] == 'E') exit_count++;
            else if (map[y][x] == 'C') obj_count++;
            else if (map[y][x] == 'P') init_pos_count++;
            x++;
        }
        y++;
    }
    if (exit_count != 1 || init_pos_count != 1)
        return (print_error("Map needs at least E, C, P and can have no more than one E and P\n"), 0);
    return (obj_count);
}

// Dimensiones del mapa:

void get_map_dimensions(char **map, int *width, int *height)
{
    int x;
    int y;

	x = 0;
	y = 0;
    *width = 0;
    *height = 0;
    while (map[x] != NULL)
    {
        y = 0;
        while (map[x][y] != '\0')
            y++;
        if (y > *width)
            *width = y;
        x++;
    }
	*width = *width -1;
    *height = x;
}
// Chequeos del mapa:
int map_checks(char **map)
{
    int width;
	int	height;
	int objects;

    get_map_dimensions(map, &width, &height);
	if (rectangular_map(map, width, height) != 1)
		return (print_error("Map must be rectangular only\n"), 0);
	printf("Dimensiones del mapa = Width (ancho) = %i Height (alto) = %i\n", width, height);
    if (!valid_walls(map, width, height) || !valid_characters(map, width, height))
        return (print_error("Map = sourrounded by wall and only valid characters\n"),
		0);
    objects = obj_exit_init_pos_count(map, width, height);
	if (objects == 0)
		return (0);
    return (objects);
};

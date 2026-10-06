/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_way_rectangular.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:11:35 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:51 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Función que comprueba que el mapa es rectangular
int	rectangular_map(char **map, int width, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if ((int)ft_strlen(map[i]) != width)
			return (0);
		i++;
	}
	return (1);
}

// Función que duplica el mapa para pasar flood-fill (que lo modifica)
char	**dup_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// Encuentra P para posicion inicial:
int	find_player(char **map, int *px, int *py)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				*px = x;
				*py = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

// Encuentra E para la salida:
int	find_exit(char **map, int *px, int *py)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'E')
			{
				*px = x;
				*py = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

// Función que valida el mapa
int	valid_path(t_ff_params *game)
{
	t_ff_params	*copy_game;

	copy_game = init_game(NULL);
	if (!find_player(game->data_map->map, &game->data_map->initial_pos.x,
			&game->data_map->initial_pos.y))
		return (free_error_print("No player in path validation", copy_game, 0));
	find_exit(game->data_map->map, &game->data_map->exit_pos.x,
		&game->data_map->exit_pos.y);
	copy_game->data_map->map = dup_map(game->data_map->map);
	if (!copy_game->data_map->map)
		return (free_error_print("Malloc fail for path", copy_game, 0));
	copy_game->height = game->height;
	copy_game->width = game->width;
	copy_game->data_map->initial_pos.x = game->data_map->initial_pos.x;
	copy_game->data_map->initial_pos.y = game->data_map->initial_pos.y;
	flood_fill(copy_game, copy_game->data_map->initial_pos.x,
		copy_game->data_map->initial_pos.y);
	if (copy_game->reach_c != game->data_map->objects)
		return (free_error_print("Not all c's reachable", copy_game, 0));
	if (!copy_game->reach_e)
		return (free_error_print("Exit not reachable", copy_game, 0));
	free_map_structs(copy_game);
	return (1);
}

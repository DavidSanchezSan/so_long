/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_way_rectangular.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:11:35 by dasanche          #+#    #+#             */
/*   Updated: 2025/08/28 18:23:42 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Función que comprueba que el mapa es rectangular
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

//Función que duplica el mapa para pasar flood-fill (lo modifica)
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

//Encuentra P para posicion inicial:
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

//Función que valida el mapa
int	valid_path(char **map, int objects)
{
	int			reached_c;
	int			reached_e;
	t_ff_params	p;
	t_coord		start;

	reached_c = 0;
	reached_e = 0;
	start.x = 0;
	start.y = 0;
	if (!find_player(map, &start.x, &start.y))
		return (print_error("No player found for path validation\n"), 0);
	p.map = dup_map(map);
	if (!p.map)
		return (print_error("Malloc failure in path validation"), 0);
	get_map_dimensions(map, &p.width, &p.height);
	p.reach_c = &reached_c;
	p.reach_e = &reached_e;
	flood_fill(&p, start.x, start.y);
	free_map(p.map);
	if (reached_c != objects)
		return (print_error("Not all collectibles reachable\n"), 0);
	if (!reached_e)
		return (print_error("Exit not reachable\n"), 0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:07:19 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/13 15:32:07 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map *init_map(t_map *data_map)
{
	data_map = malloc(sizeof(t_map));
	if(!data_map)
	{
		print_error("Failed memory allocation for data_map\n");
		return (NULL);
	}
	data_map->map = NULL;
	data_map->x = 0;
	data_map->y = 0;
	data_map->objects = 0;
	data_map->exits = 0;
	data_map->initial_pos.x = 0;
	data_map->initial_pos.y = 0;
	return(data_map);
}

t_ff_params *init_game(t_ff_params *game)
{
	game = malloc(sizeof(t_ff_params));
	if(!game)
	{
		print_error("Failed memory allocation for game params\n");
		return (NULL);
	}
	game->data_map = init_map(game->data_map);
	game->width = 0;
	game->height = 0;
	game->reach_c = 0;
	game->reach_e = 0;
	return (game);
}

int	main(int argc, char **argv)
{
	// Revisado 1 vez:
	t_ff_params	*game;
	int			i;

	i = 0;
	game = NULL;
	if (argc != 2)
	{
		print_error("Program must be launched with 2 arguments.\n");
		return (1);
	}
	if (!ber_extension_validation(argv[1]))
		exit (1);
	game = init_game(game);
	if (!read_map(argv[1], game))
		return (free_map(game->data_map->map), (2));
	// Por revisar:
	if (map_checks(game) != 1)
		return(free_map(game->data_map->map), (3));
	printf("Map objects: %i\n", game->data_map->objects);
	printf("Mapa cargado:\n");
	while (game->data_map->map[i] != NULL)
	{
		printf("%s\n", game->data_map->map[i]);
		i++;
	}
	free_map(game->data_map->map);
	return (0);
}

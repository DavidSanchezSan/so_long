/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:07:19 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:47 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Inicializo el mapa:
t_map	*init_map(t_map *data_map)
{
	data_map = malloc(sizeof(t_map));
	if (!data_map)
	{
		print_error("Failed memory allocation for data_map\n");
		return (NULL);
	}
	data_map->map = NULL;
	data_map->x = 0;
	data_map->y = 0;
	data_map->objects = 0;
	data_map->exits = 0;
	data_map->exit_pos.x = 0;
	data_map->exit_pos.y = 0;
	data_map->initial_pos.x = 0;
	data_map->initial_pos.y = 0;
	return (data_map);
}

//Inicializo el juego:
t_ff_params	*init_game(t_ff_params *game)
{
	game = malloc(sizeof(t_ff_params));
	if (!game)
	{
		print_error("Failed memory allocation for game params\n");
		return (NULL);
	}
	game->data_map = NULL;
	game->data_map = init_map(game->data_map);
	game->width = 0;
	game->height = 0;
	game->reach_c = 0;
	game->reach_e = 0;
	game->steps = 0;
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->tile_size = 128;
	game->image_wall = NULL;
	return (game);
}

//Aseguro que el mapa cabe en la pantalla:
int	ensure_map_size(t_ff_params *game)
{
	int	screen_x;
	int	screen_y;

	mlx_get_screen_size(game->mlx, &screen_x, &screen_y);
	if (((game->width * game->tile_size) > screen_x) || (game->height
			* game->tile_size) > screen_y)
	{
		print_error("Map is too big!\nTry another size\n");
		return (1);
	}
	return (0);
}

// Parseo completo del mapa:
int	parsing_map(int argc, char **argv, t_ff_params *game)
{
	if (argc != 2)
		return (print_error("Program must be launched with 2 arguments.\n"), 1);
	if (!ber_extension_validation(argv[1]))
		return (2);
	if (!read_map(argv[1], game))
		return (free_map_structs(game), (3));
	if (map_checks(game) != 1)
		return (free_map_structs(game), (4));
	return (0);
}

//Main:
int	main(int argc, char **argv)
{
	t_ff_params	*game;

	game = NULL;
	game = init_game(game);
	if (parsing_map(argc, argv, game) != 0)
		return (5);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free_error_print("Initializing MLX", game, 6));
	if (ensure_map_size(game) != 0)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (free_map_structs(game), 7);
	}
	game->mlx_win = mlx_new_window(game->mlx, game->width * game->tile_size,
			game->height * game->tile_size, "So_Long");
	if (!game->mlx_win)
		return (free_error_print("Creating window", game, 8));
	init_images(game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_handler, game);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
	render_map(game, game->data_map->map);
	mlx_loop(game->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:07:19 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/16 16:05:16 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_ff_params *game)
{
	printf("Map objects: %i\n", game->data_map->objects);
	printf("Mapa cargado:\n");
	for (int i = 0; game->data_map->map[i] != NULL; i++)
		printf("%s\n", game->data_map->map[i]);
}

void	free_map_structs(t_ff_params *game)
{
	if (game->data_map->map)
		free_map(game->data_map->map);
	if (game->data_map)
		free(game->data_map);
	if (game)
		free(game);
}

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
	data_map->initial_pos.x = 0;
	data_map->initial_pos.y = 0;
	return (data_map);
}

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
	game->mlx = NULL;
	game->mlx_win = NULL;
	return (game);
}

int	close_window(t_ff_params *game)
{
	if (game->mlx && game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	game->mlx_win = NULL;
	mlx_loop_end(game->mlx);
	return (0);
}

int	key_handler(int keycode, t_ff_params *game)
{
	(void)game;
	if (keycode == 65307)
	{
		printf("CLOSE GAME\n");
		printf("%i\n", keycode);
		close_window(game);
	}
	else if (keycode == 97 || keycode == 65361)
		printf("LEFT (A / ARROW_LEFT)\n");
	else if (keycode == 119 || keycode == 65362)
		printf("UP (W / ARROW_UP)\n");
	else if (keycode == 100 || keycode == 65363)
		printf("RIGHT (D / ARROW_RIGHT)\n");
	else if (keycode == 115 || keycode == 65364)
		printf("DOWN (S / ARROW_DOWN)\n");
	else
	{
		printf("%d\n", keycode);
	}
	fflush(stdout); //BORRAR!!!!
	return (0);
}

int	main(int argc, char **argv)
{
	t_ff_params	*game;

	game = NULL;
	if (argc != 2)
	{
		print_error("Program must be launched with 2 arguments.\n");
		return (1);
	}
	if (!ber_extension_validation(argv[1]))
		exit(1);
	game = init_game(game);
	if (!read_map(argv[1], game))
		return (free_map_structs(game), (2));
	// Por revisar:
	if (map_checks(game) != 1)
		return (free_map_structs(game), (3));
	print_map(game);
	game->mlx = mlx_init();
	//Lógica del juego:
	game->mlx_win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "So_Long");
	mlx_hook(game->mlx_win, 2, 1L << 0, key_handler, game); // Hook para teclas
	mlx_hook(game->mlx_win, 17, 0, close_window, game); //Hook de cerrar ventana
	// mlx_loop_hook(mlx, render_frame, game);  // Lógica de renderizado
	mlx_loop(game->mlx);
	mlx_loop_end(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map_structs(game);
	return (0);
}

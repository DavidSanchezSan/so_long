/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:07:19 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/23 17:14:01 by dasanche         ###   ########.fr       */
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
	game->tile_size = 200;
	game->image_wall = NULL;
	return (game);
}

int	close_window(t_ff_params *game)
{
	if (game->mlx && game->mlx_win)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		game->mlx_win = NULL;
	}
	mlx_loop_end(game->mlx);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free_map_structs(game);
	exit(0);
	return (0);
}

int	key_handler(int keycode, t_ff_params *game)
{
	(void)game;
	printf("%i\n", keycode);
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
	return (0);
}

int	mouse_handler(int button, int x, int y, t_ff_params *game)
{
	(void)game;
	printf("Mouse button %d clicked at (%d, %d)\n", button, x, y);
	return (0);
}
// ########################################################################################
void	*load_image(const char *filename, int *image_width, t_ff_params *game)
{
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, (char *)filename, image_width,
			image_width);
	if (!img)
	{
		printf("Error al cargar la imagen XPM\n");
		exit(1);
	}
	return (img);
}

void	init_images(t_ff_params *game)
{
	game->image_wall = load_image("Estrellita.xpm", &game->tile_size, game);
	// game->image_floor =
	// game->image_player =
	// game->image_collectible =
	// game->image_exit =
}

void	render_map(t_ff_params *game, char **map)
{
	for (int i = 0; map[i]; i++)
	{
		for (int x = 0; map[i][x]; x++)
		{
			if (map[i][x] == '1')
			{
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->image_wall, x * game->tile_size, i * game->tile_size);
			}
		}
	}
}
// ########################################################################################

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
	if (!game->mlx)
	{
		free_map_structs(game);
		print_error("Error initializing MLX\n");
		exit(1);
	}
	// Lógica del juego:
	game->mlx_win = mlx_new_window(game->mlx, game->width * game->tile_size,
			game->height * game->tile_size, "So_Long");
	if (!game->mlx_win)
	{
		free_map_structs(game);
		print_error("Error creating window\n");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(1);
	}
	init_images(game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_handler, game); // Hook para teclas
	mlx_hook(game->mlx_win, 4, 1L << 2, mouse_handler, game); // Hook para ratón
	mlx_hook(game->mlx_win, 17, 0, close_window, game); // Hook de cerrar ventana
	render_map(game, game->data_map->map);
	// mlx_loop_hook(mlx, render_frame, game);  // Lógica de renderizado
	mlx_loop(game->mlx);
	return (0);
}

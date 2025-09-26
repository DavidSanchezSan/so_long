/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:07:19 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/25 16:57:38 by dasanche         ###   ########.fr       */
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
	data_map->exit_pos.x = 0;
	data_map->exit_pos.y = 0;
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
	game->steps = 0;
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->tile_size = 64;
	game->image_wall = NULL;
	return (game);
}

int ensure_map_size(t_ff_params *game)
{
	int screen_x;
	int screen_y;

	mlx_get_screen_size(game->mlx, &screen_x, &screen_y);
	if (((game->width * game->tile_size) > screen_x) || (game->height * game->tile_size) > screen_y)
	{
		print_error("Map is too big!\nTry another size\n");
		return (1);
	}
	return (0);
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
		mlx_destroy_image(game->mlx, game->image_collectible);
		mlx_destroy_image(game->mlx, game->image_exit);
		mlx_destroy_image(game->mlx, game->image_floor);
		mlx_destroy_image(game->mlx, game->image_player);
		mlx_destroy_image(game->mlx, game->image_wall);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free_map_structs(game);
	exit(1);
	return (0);
}

int	key_handler(int keycode, t_ff_params *game)
{
	(void)game;
	int	new_x;
	int	new_y;
	
	new_x = game->data_map->initial_pos.x;
	new_y = game->data_map->initial_pos.y;
	// printf("%i\n", keycode);
	if (keycode == 65307)
	{
		printf("CLOSE GAME\n");
		// printf("%i\n", keycode);
		close_window(game);
	}
	else if (keycode == 97 || keycode == 65361)
	{
		new_x -= 1;
		// printf("LEFT (A / ARROW_LEFT)\n");
	}
	else if (keycode == 119 || keycode == 65362)
	{
		new_y -= 1;
		// printf("UP (W / ARROW_UP)\n");
	}
	else if (keycode == 100 || keycode == 65363)
	{
		new_x += 1;
		// printf("RIGHT (D / ARROW_RIGHT)\n");
	}
	else if (keycode == 115 || keycode == 65364)
	{
		new_y += 1;
		// printf("DOWN (S / ARROW_DOWN)\n");
	}
	else
	{
		// printf("%d\n", keycode);
	}
	move_player(game, new_x, new_y);
	return (0);
}

void	move_player(t_ff_params *game, int new_x, int new_y)
{
	if (game->data_map->map[new_y][new_x] == '1')
		return ;
	game->steps++;
	printf("Pasos dados: %d\n", game->steps);
	if (game->data_map->map[game->data_map->initial_pos.y][game->data_map->initial_pos.x] != 'E')
		game->data_map->map[game->data_map->initial_pos.y][game->data_map->initial_pos.x] = '0';
	if ((game->data_map->initial_pos.y == game->data_map->exit_pos.y) && (game->data_map->initial_pos.x == game->data_map->exit_pos.x) && (game->data_map->objects != 0))
		game->data_map->map[game->data_map->initial_pos.y][game->data_map->initial_pos.x] = 'E';
	game->data_map->initial_pos.x = new_x;
	game->data_map->initial_pos.y = new_y;
	if (game->data_map->map[new_y][new_x] == 'C')
		game->data_map->objects -= 1;
	if ((game->data_map->map[new_y][new_x] == 'E') && (game->data_map->objects == 0))
	{
		printf("Has terminado el juego con %d pasos\n", game->steps);
		close_window(game);
		return ;
	}
	game->data_map->map[game->data_map->initial_pos.y][game->data_map->initial_pos.x] = 'P';
	render_map(game, game->data_map->map);
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
	game->image_wall = load_image("srcs/images/Tree_01.xpm", &game->tile_size, game);
	game->image_floor = load_image("srcs/images/Grass_01.xpm", &game->tile_size, game);
	game->image_player = load_image("srcs/images/Marceline_01.xpm", &game->tile_size, game);
	game->image_collectible = load_image("srcs/images/Bass_01.xpm", &game->tile_size, game);
	game->image_exit = load_image("srcs/images/Portal_01.xpm", &game->tile_size, game);
}
void	render_map(t_ff_params *game, char **map)
{
	for (int i = 0; map[i]; i++)
	{
		for (int x = 0; map[i][x]; x++)
		{
			if (map[i][x] == '0')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->image_floor, x * game->tile_size, i * game->tile_size);
			if (map[i][x] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->image_wall, x * game->tile_size, i * game->tile_size);
			if (map[i][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->image_player, x * game->tile_size, i * game->tile_size);
			if (map[i][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->image_collectible, x * game->tile_size, i * game->tile_size);
			if (map[i][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->image_exit, x * game->tile_size, i * game->tile_size);
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
	// print_map(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_map_structs(game);
		print_error("Initializing MLX\n");
		return (1);
	}
	if (ensure_map_size(game) != 0)
	{
		mlx_destroy_display(game->mlx);
		if (game->mlx)
			free(game->mlx);
		free_map_structs(game);
		return (1);
	}
	// Lógica del juego:
	game->mlx_win = mlx_new_window(game->mlx, game->width * game->tile_size,
			game->height * game->tile_size, "So_Long");
	if (!game->mlx_win)
	{
		free_map_structs(game);
		print_error("Creating window\n");
		return (1);
	}
	init_images(game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_handler, game); // Hook para teclas
	mlx_hook(game->mlx_win, 4, 1L << 2, mouse_handler, game); // Hook para ratón
	mlx_hook(game->mlx_win, 17, 0, close_window, game); // Hook de cerrar ventana
	render_map(game, game->data_map->map);
	mlx_loop(game->mlx);
	return (0);
}

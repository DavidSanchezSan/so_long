/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:36:00 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:53 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Función que gestiona los mensajes del teclado:
int	key_handler(int keycode, t_ff_params *game)
{
	int	new_x;
	int	new_y;

	(void)game;
	new_x = game->data_map->initial_pos.x;
	new_y = game->data_map->initial_pos.y;
	if (keycode == 65307)
	{
		ft_printf("CLOSE GAME\n");
		close_window(game);
	}
	else if (keycode == 97 || keycode == 65361)
		new_x -= 1;
	else if (keycode == 119 || keycode == 65362)
		new_y -= 1;
	else if (keycode == 100 || keycode == 65363)
		new_x += 1;
	else if (keycode == 115 || keycode == 65364)
		new_y += 1;
	move_player(game, new_x, new_y);
	return (0);
}

//Función mueve el personaje:
void	move_player(t_ff_params *game, int new_x, int new_y)
{
	t_coord	init;

	init.x = game->data_map->initial_pos.x;
	init.y = game->data_map->initial_pos.y;
	if (game->data_map->map[new_y][new_x] == '1')
		return ;
	game->steps++;
	ft_printf("Pasos dados: %d\n", game->steps);
	if (game->data_map->map[init.y][init.x] != 'E')
		game->data_map->map[init.y][init.x] = '0';
	if ((init.y == game->data_map->exit_pos.y)
		&& (init.x == game->data_map->exit_pos.x)
		&& (game->data_map->objects != 0))
		game->data_map->map[init.y][init.x] = 'E';
	game->data_map->initial_pos.x = new_x;
	game->data_map->initial_pos.y = new_y;
	if (game->data_map->map[new_y][new_x] == 'C')
		game->data_map->objects -= 1;
	if ((game->data_map->map[new_y][new_x] == 'E')
		&& (game->data_map->objects == 0))
		return (finish_game(game));
	game->data_map->map[new_y][new_x] = 'P';
	render_map(game, game->data_map->map);
}

//Función que cierra la ventana y libera memoria:
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

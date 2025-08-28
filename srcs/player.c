/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:28:37 by dasanche          #+#    #+#             */
/*   Updated: 2025/08/28 16:50:41 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Cambiar la lógica `move_player` para reflejar posición del jugador bien:
// void	move_player(t_game *game, int dx, int dy)
// {
// 	int	new_x;
// 	int	new_y;

// 	new_x = game->player_x + dx;
// 	new_y = game->player_y + dy;
// 	if (get_map_cell(new_x, new_y) != '1') // Si no es una pared
// 	{
// 		// Redibujar solo el jugador en la nueva posición
// 		mlx_clear_window(game->mlx, game->win); // Limpia toda la ventana
// 		game->player_x = new_x;
// 		game->player_y = new_y;
// 		draw_map(game); // Redibujar el mapa con la nueva posición del jugador
// 	}
// }

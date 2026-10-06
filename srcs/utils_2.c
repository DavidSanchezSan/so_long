/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:28:17 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:57 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Función para liberar el mapa en su totalidad
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

// Función para liberar map_structs y mensaje de error: 
int	free_error_print(char *msg, t_ff_params *game, int ret)
{
	free_map_structs(game);
	print_error(msg);
	write(1, "\n", 1);
	return (ret);
}

// Dimensiones del mapa:
void	get_map_dimensions(char **map, int *width, int *height)
{
	int	i;

	*width = 0;
	*height = 0;
	i = 0;
	while (map[i] != NULL)
	{
		if ((int)ft_strlen(map[i]) > *width)
			*width = ft_strlen(map[i]);
		i++;
	}
	*height = i;
}

// Informa del fin del juego, imprime los pasos y cierra la ventana:
void	finish_game(t_ff_params *game)
{
	ft_printf("Has terminado el juego con %d pasos\n", game->steps);
	close_window(game);
}

//Libera la estructura game y su contenido:
void	free_map_structs(t_ff_params *game)
{
	if (game->data_map->map)
		free_map(game->data_map->map);
	if (game->data_map)
		free(game->data_map);
	if (game)
		free(game);
}

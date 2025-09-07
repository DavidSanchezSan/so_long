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

int rectangular_map(char **map, int width, int height)
{
    int i;

    i = 0;
    while (i < height)
    {
        if ((int)ft_strlen(map[i]) != width)
            return (0);
        i++;
    }
    return (1);
}
// #include "so_long.h"

// static void flood_fill(char **map, int x, int y, int height, int width)
// {
//     if (x < 0 || y < 0 || x >= height || y >= width)
//         return;
//     if (map[x][y] == '1' || map[x][y] == 'V')
//         return;

//     map[x][y] = 'V';

//     flood_fill(map, x + 1, y, height, width);
//     flood_fill(map, x - 1, y, height, width);
//     flood_fill(map, x, y + 1, height, width);
//     flood_fill(map, x, y - 1, height, width);
// }

// int valid_path(char **map, int width, int height)
// {
//     int x, y;
//     int player_x = -1, player_y = -1;

//     // 1️⃣ Buscar la posición inicial del jugador
//     for (x = 0; x < height; x++)
//     {
//         for (y = 0; y < width; y++)
//         {
//             if (map[x][y] == 'P')
//             {
//                 player_x = x;
//                 player_y = y;
//                 break;
//             }
//         }
//         if (player_x != -1) break;
//     }

//     if (player_x == -1)
//         return (print_error("No starting position found\n"), 0);

//     // 2️⃣ Hacer una copia del mapa porque flood_fill lo modifica
//     char **map_copy = malloc(sizeof(char *) * (height + 1));
//     if (!map_copy)
//         return (0);
//     for (int i = 0; i < height; i++)
//         map_copy[i] = ft_strdup(map[i]);
//     map_copy[height] = NULL;

//     // 3️⃣ Ejecutar flood_fill desde la posición del jugador
//     flood_fill(map_copy, player_x, player_y, height, width);

//     // 4️⃣ Verificar que todos los 'C' y al menos un 'E' fueron visitados
//     int exit_found = 0;
//     for (x = 0; x < height; x++)
//     {
//         for (y = 0; y < width; y++)
//         {
//             if (map[x][y] == 'C' && map_copy[x][y] != 'V')
//                 return (free_map(map_copy), print_error("Not all collectibles reachable\n"), 0);
//             if (map[x][y] == 'E' && map_copy[x][y] == 'V')
//                 exit_found = 1;
//         }
//     }

//     free_map(map_copy);
//     if (!exit_found)
//         return (print_error("No valid path to exit\n"), 0);
//     return (1);
// }

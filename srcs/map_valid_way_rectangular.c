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
    int x;

    x = 0;
    while (x < height) // Compruebo si todas las filas tienen la longitud correcta (con salto de línea en las intermedias)
    {
        size_t row_len = ft_strlen(map[x]);
        if (x < height - 1) // Para las filas intermedias (excepto la última), la longitud debe ser width + 1
		{
            if ((int)row_len != width + 1)
			{
                // printf("Error en fila %d: longitud esperada %d, obtenida %zu\n", x, width + 1, row_len);
                return (0);  // No es rectangular si la fila intermedia no tiene longitud esperada
            }
        }
        else // Para la última fila, la longitud debe ser width (sin salto de línea)
		{
            if ((int)row_len != width)
			{
                // printf("Error en la última fila: longitud esperada %d, obtenida %zu\n", width, row_len);
                return (0);  // No es rectangular si la última fila no tiene longitud esperada
            }
        }
        x++;
    }
    if (height == width) // Comprobamos que no sea cuadrado
	{
		// printf("Error es un cuadrado");
		return (0);  // Si es cuadrado (altura == ancho), no es un rectángulo
	}
    if (ft_strlen(map[0]) - 1 != (ft_strlen(map[height - 1]))) // Comprobamos si las filas superior e inferior tienen la misma longitud
	{
		// printf("Filas diferentes superior e inferior");
		return (0);  // No es rectangular si no son iguales
	}
    return (1);
}

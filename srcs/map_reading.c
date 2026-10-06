/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:21:43 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:49 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Cuenta cuántas líneas tiene el archivo:
static int	count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

// Función auxiliar para liberar el mapa:
static void	free_partial_map(char **map, int count)
{
	if (!map)
		return ;
	while (count-- > 0)
		free(map[count]);
	free(map);
}

static void	drain_fd(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

// Función para leer linea a linea y eliminar el salto de linea leida:
static char	**fill_map(int fd, int lines)
{
	char	**map;
	char	*line;
	int		i;
	size_t	len;

	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		line = get_next_line(fd);
		if (!line)
			return (drain_fd(fd), free_partial_map(map, i), NULL);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (line[0] == '\0')
			return (free(line), drain_fd(fd), free_partial_map(map, i),
				print_error("Map contains empty lines\n"), NULL);
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	return (map);
}

// Función para abrir/leer y devolver el mapa sin saltos de linea:
char	**read_map(char *filename, t_ff_params *game)
{
	int	fd;
	int	lines;

	fd = open_file(filename);
	if (fd < 0)
		return (NULL);
	lines = count_lines(fd);
	close(fd);
	if (lines == 0)
	{
		print_error("Map is empty\n");
		return (NULL);
	}
	fd = open_file(filename);
	if (fd < 0)
		return (NULL);
	game->data_map->map = fill_map(fd, lines);
	close(fd);
	return (game->data_map->map);
}

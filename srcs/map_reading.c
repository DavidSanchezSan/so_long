/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:21:43 by dasanche          #+#    #+#             */
/*   Updated: 2025/08/23 17:16:51 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Map-file could not be opened\n");
	return (fd);
}

char	**resize_map(int lines_allocated)
{
	char	**new_map;

	new_map = malloc(sizeof(char *) * lines_allocated);
	if (!new_map)
		return (NULL);
	return (new_map);
}

char	**get_map(int fd, int *lines_allocated, char **map)
{
	int		count;
	char	*line;
	char	**new_map;
	char	*temp_line;

	count = 0;
	temp_line = get_next_line(fd);
	while (temp_line != NULL)
	{
		line = temp_line;
		temp_line = get_next_line(fd);
		new_map = resize_map(*lines_allocated * 2);
		if (!new_map)
			return (free_map(map), close(fd), NULL);
		if (count >= *lines_allocated)
		{
			*map = *new_map;
			*lines_allocated *= 2;
		}
		map[count++] = line;
	}
	map[count] = NULL;
	return (map);
}

char	**read_map(char *filename)
{
	int		fd;
	int		lines_allocated;
	char	**map;

	fd = open_file(filename);
	if (fd < 0)
		return (NULL);
	lines_allocated = 16;
	map = malloc(sizeof(char *) * lines_allocated);
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	map = get_map(fd, &lines_allocated, map);
	close(fd);
	return (map);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

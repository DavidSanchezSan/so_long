/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:02:18 by dasanche          #+#    #+#             */
/*   Updated: 2025/03/26 15:49:37 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stored;
	char		*line;
	char		*temp;
	int			bytes_read;
	int			to_end;

	line = NULL;
	temp = NULL;
	bytes_read = 1;
	to_end = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	// if (BUFFER_SIZE < 1 || fd < 0)
	// 	return(NULL);
	if (buffer == NULL)
	{
		printf("Error de memoria");
		return (NULL);
	}
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			printf("Error de lectura");
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (stored == NULL && bytes_read == 0)
		{
			free(buffer);
			return (NULL);
		}
		if (stored == NULL)
			stored = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(stored, buffer);
			free(stored);
			stored = temp;
		}
		if (ft_strchr(stored, '\n') != NULL)
			break ;
	}
	if (ft_strchr(stored, '\n') != NULL)
	{
		while (stored[to_end] != '\n' && stored[to_end] != '\0')
			to_end++;
		line = ft_substr(stored, 0, to_end + 1);
		temp = ft_substr(stored, to_end + 1, (ft_strlen(stored) - to_end - 1));
		free(stored);
		stored = temp;
	}
	else if (bytes_read == 0 && stored != NULL)
	{
		line = ft_strdup(stored);
		free(stored);
		stored = NULL;
	}
	free(buffer);
	return (line);
}

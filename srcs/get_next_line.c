/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:02:18 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/25 16:53:45 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*ft_join_free(char *buffer, char *stored)
{
	char	*temp;

	temp = ft_strjoin(stored, buffer);
	free(stored);
	return (temp);
}

static char	*ft_read_line(int *fd, int *bytes_read, char *buffer, char *stored)
{
	while (*bytes_read > 0)
	{
		*bytes_read = read(*fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			free(stored);
			stored = NULL;
			return (NULL);
		}
		buffer[*bytes_read] = '\0';
		if (stored == NULL && *bytes_read == 0)
			return (NULL);
		if (stored == NULL)
			stored = ft_strdup("");
		stored = ft_join_free(buffer, stored);
		if (ft_strchr(stored, '\n') != NULL)
			break ;
	}
	return (stored);
}

char	*ret_line(char *line, char **stored)
{
	if ((*stored)[0] == '\0')
		return (ft_cleanup_stored(stored, NULL));
	else
		return (line = ft_strdup(*stored), ft_cleanup_stored(stored, line));
}

static char	*ft_find_line(char **stored, int bytes_read)
{
	char	*line;
	char	*temp;
	int		to_end;

	line = NULL;
	temp = NULL;
	to_end = 0;
	if (ft_strchr(*stored, '\n') != NULL)
	{
		while ((*stored)[to_end] != '\n' && (*stored)[to_end] != '\0')
			to_end++;
		line = ft_substr(*stored, 0, to_end + 1);
		temp = ft_substr(*stored, to_end + 1, ft_strlen(*stored) - to_end - 1);
		free(*stored);
		if (temp[0] == '\0')
		{
			free(temp);
			*stored = NULL;
		}
		else
			*stored = temp;
	}
	else if (bytes_read == 0 && *stored != NULL)
		return (ret_line(line, stored));
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stored[1024];
	char		*line;
	int			bytes_read;

	line = NULL;
	bytes_read = 1;
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	stored[fd] = ft_read_line(&fd, &bytes_read, buffer, stored[fd]);
	if (!stored[fd])
		return (free(buffer), stored[fd] = NULL, NULL);
	line = ft_find_line(&stored[fd], bytes_read);
	free(buffer);
	buffer = NULL;
	return (line);
}

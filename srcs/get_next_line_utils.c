/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:02:14 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/25 16:53:48 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Function function returns a pointer to a new string which is a duplicate of
// the string s.  Memory for the new string is obtained with malloc, and can
// be freed with free.

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	copy = malloc(len + 1);
	if (copy == NULL)
		return (NULL);
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}

// Function that returns a pointer to the first matched character
// or NULL if the character is not found.

char	*ft_strchr(const char *s, int c)
{
	char	a;

	a = (char)c;
	while (*s != '\0')
	{
		if (*s == a)
			return ((char *)s);
		s++;
	}
	if (a == '\0')
		return ((char *)s);
	return (NULL);
}

// Function that returns the length of a string

size_t	ft_strlen(const char *s)
{
	size_t	x;

	if (!s)
		return (0);
	x = 0;
	while (s[x] != '\0')
	{
		x++;
	}
	return (x);
}

// Reserves with malloc and returns a new string,
// formed by the concatenation of ‘s1’ and ‘s2’.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_string[i] = s2[j];
		i++;
		j++;
	}
	new_string[i] = '\0';
	return (new_string);
}

// Reserves and returns a substring of the string ‘s’.
// The substring starts from ‘start’ and has maximum length: ‘len’.

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	i = 0;
	if (s == NULL || start >= ft_strlen(s) || len <= 0)
	{
		subs = malloc(1 * sizeof(char));
		if (subs == NULL)
			return (NULL);
		subs[0] = '\0';
		return (subs);
	}
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (len + start > ft_strlen(s))
		subs = malloc(len * sizeof(char) + 1);
	else
		subs = malloc((len + 1) * sizeof(char));
	if (subs == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
		subs[i++] = s[start++];
	subs[i] = '\0';
	return (subs);
}

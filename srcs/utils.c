#include "so_long.h"

void print_error(char *msg)
{
    write(2, "Error\n", 6);
    write(2, msg, ft_strlen(msg));
}

char *ft_strrchr(char *s, int c)
{
    char *last;
	last = NULL;
    while (*s)
    {
        if (*s == (char)c)
            last = (char *)s;
        s++;
    }
    if (c == '\0')
        return (char *)s;
    return (last);
}

int	ber_extension_validation(char *name_map)
{
	int		i;
    char	*file_name;

	if (!name_map)
    {
		print_error("No map name.\n");
        return(0);
    }
    file_name = ft_strrchr(name_map, '/');
    if (file_name == NULL)
        file_name = name_map;
    else
        file_name++;
    i = ft_strlen(file_name);
    if (i < 5)
    {
        print_error("Map file must have a name and .ber extension.\n");
        return (0);
    }
    if (file_name[i - 4] != '.' || file_name[i - 3] != 'b' ||
        file_name[i - 2] != 'e' || file_name[i - 1] != 'r')
    {
        print_error("Map file must have a name and .ber extension.\n");
        return (0);
    }
    return (1);
}
#include "so_long.h"

void print_error(char *msg)
{
    write(2, "Error\n", 6);
    write(2, msg, ft_strlen(msg));
}

int	ber_extension_validation(char *name_map)
{
	int	i;

	if (!name_map)
    {
		print_error("No map name.\n");
        return(0);
    }
	i = ft_strlen(name_map);
	if (i < 5)
    {
		print_error("Map file must have a .ber extension.\n");
        return(0);
    }
	if (name_map[i - 4] != '.' || name_map[i - 3] != 'b' ||
		name_map[i - 2] != 'e' || name_map[i - 1] != 'r')
    {
		print_error("Map file must have a .ber extension.\n");
        return (0);
    }
    return (1);
}
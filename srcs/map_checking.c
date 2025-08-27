#include "so_long.h"


int valid_characters(char **map, int width, int height)
{
    int x;
    int y;

    x = 0;
    while (x < height)
    {
        y = 0;
        while (y < width)
        {
            if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != 'C'
            && map[x][y] != 'E' && map[x][y] != 'P')
                return (0);
            y++;
        }
        x++;
    }
    return (1);
}

int valid_walls(char **map, int width, int height)
{
    int x;

    x = 0;
    while (x < width)
    {
        if (map[0][x] != '1' || map[height - 1][x] != '1')
            return (0);
        x++;
    }
    x = 0;
    while (x < height)
    {
        if (map[x][0] != '1' || map[x][width - 1] != '1')
            return (0);
        x++;
    }

    return (1);
}

int map_checks(char **map)
{
    int x;
    int y;
    int width;
    int height;

    width = 0;
    height = 0;
    x = 0;
    while (map[x] != NULL)
    {
        y = 0;
        while (map[x][y] != '\0')
            y++;
        if (y > width)
            width = y;
        x++;
    }
    height = x;
    if (!valid_walls(map, width, height) || !valid_characters(map, width, height))
    {
        print_error("Map must be surrounded by walls and contain only valid characters");
        return (0);
    }
    return (1);
}

//########################################################################################

int open_file(char *filename)
{
    int fd;
    
    fd= open(filename, O_RDONLY);
    if (fd < 0)
        print_error("Map-file could not be opened\n");
    return (fd);
}

char **resize_map(int lines_allocated)
{
    char **new_map;
    
    new_map = malloc(sizeof(char *) * lines_allocated);
    if (!new_map)
        return (NULL);
    return (new_map);
}

char **get_map(int fd, int *lines_allocated, char **map)
{
    int count;
    char *line;
    char **new_map;

    count = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (count >= *lines_allocated)
        {
            new_map = resize_map(*lines_allocated * 2);
            if (!new_map)
            {
                free_map(map);
                close(fd);
                return (NULL);
            }
            map = new_map;
            *lines_allocated *= 2;
        }
        map[count] = line;
        count++;
    }
    map[count] = NULL;
    return (map);
}


char **read_map(char *filename)
{
    int fd;
    int lines_allocated;
    char **map;

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

void free_map(char **map)
{
    int i;
    
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

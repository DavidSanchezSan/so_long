#include "so_long.h"

int valid_characters(char c)
{
    return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

int valid_walls(char **map, int width, int height)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while(x < width)
    {
        if (map[0][x] != '1' || map[height - 1][x] != '1')
            return (0);
    x++;
    }
    while(y < height)
    {
        if (map[y][0] != '1' || map[y][width - 1] != '1')
            return (0);
    y++;
    }
    return (1);
}

char **read_map(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char **map = NULL;
    char *line = NULL;
    int lines_allocated = 16;
    int count = 0;

    map = malloc(sizeof(char *) * (lines_allocated + 1));
    if (!map)
    {
        close(fd);
        return NULL;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        if (count >= lines_allocated)
        {
            lines_allocated *= 2;
            char **tmp = realloc(map, sizeof(char *) * (lines_allocated + 1));
            if (!tmp)
            {
                // liberar memoria
                for (int i = 0; i < count; i++)
                    free(map[i]);
                free(map);
                free(line);
                close(fd);
                return NULL;
            }
            map = tmp;
        }
        map[count++] = line;
    }
    map[count] = NULL;
    close(fd);
    return map;
}

void free_map(char **map)
{
    if (!map)
        return;

    for (int i = 0; map[i] != NULL; i++)
        free(map[i]);

    free(map);
}
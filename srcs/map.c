#include "so_long.h"

// Representación del mapa: 1 es pared, 0 es espacio vacío, 9 es el objetivo
char *map[MAP_HEIGHT] =
{
    "1111111111",
    "1000000001",
    "1010101001",
    "1000000001",
    "1090000001",
    "1000000001",
    "10000000E1",
    "1111111111"
};

// Función para obtener un valor de la celda del mapa
char get_map_cell(int x, int y)
{
    if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT || map[y] == NULL)
        return ' ';  // Fuera del mapa
    return map[y][x];
}

void draw_map(t_game *game)
{
    int x, y;
    int screen_x, screen_y;

    // Recorrer cada celda del mapa
    y = 0;
    while (y < MAP_HEIGHT)
    {
        x = 0;
        while (x < MAP_WIDTH)
        {
            screen_x = x * CELL_SIZE;
            screen_y = y * CELL_SIZE;

            // Dibujar paredes
            if (game->map[y][x] == '1')
                mlx_string_put(game->mlx, game->win, screen_x + 10, screen_y + 10, 0xFFFFFF, "#"); // Pared
            // Dibujar el objetivo
            else if (game->map[y][x] == '9')
                mlx_string_put(game->mlx, game->win, screen_x + 10, screen_y + 10, 0xFFFF00, "O"); // Objetivo
            // Dibujar el escape
            else if (game->map[y][x] == 'E')
                mlx_string_put(game->mlx, game->win, screen_x + 10, screen_y + 10, 0xFF00FF, "E"); // Escape
            // Dibujar espacios vacíos
            else
                mlx_string_put(game->mlx, game->win, screen_x + 10, screen_y + 10, 0x0000FF, " "); // Espacio vacío
            x++;
        }
        y++;
    }

    // Asegurarse de que el jugador siempre se dibuje al final (en el caso de que el jugador no se haya sobreescrito con 'P')
    mlx_string_put(game->mlx, game->win, game->player_x * CELL_SIZE + 10, game->player_y * CELL_SIZE + 10, 0xFF0000, "P");
}

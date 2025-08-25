
#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mlx.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define CELL_SIZE 64
# define MAP_WIDTH 10
# define MAP_HEIGHT 8


// Estructura para gestionar el estado del juego
typedef struct s_game
{
    void    *mlx;        // Conexión con la biblioteca mlx
    void    *win;        // Ventana del juego
    char    **map;       // Mapa del juego
    int     player_x;    // Posición X del jugador
    int     player_y;    // Posición Y del jugador
} t_game;

int     key_hook(int keycode, void *param);
int     close_game(t_game *game);
void    move_player(t_game *game, int dx, int dy);
char    get_map_cell(int x, int y);
void    draw_map(t_game *game);

#endif
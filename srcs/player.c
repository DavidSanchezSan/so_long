#include "so_long.h"

// Cambiar la lógica de `move_player` para reflejar la posición del jugador correctamente:
void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    if (get_map_cell(new_x, new_y) != '1')  // Si no es una pared
    {
        // Redibujar solo el jugador en la nueva posición
        mlx_clear_window(game->mlx, game->win);  // Limpia toda la ventana (subóptimo)
        game->player_x = new_x;
        game->player_y = new_y;
        draw_map(game);  // Redibujar el mapa con la nueva posición del jugador
    }
}


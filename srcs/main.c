#include "so_long.h"

// extern char *map[];  // Declaración externa del mapa

// int close_game(t_game *game)
// {
//     mlx_destroy_window(game->mlx, game->win);  // Liberar ventana
//     mlx_destroy_display(game->mlx);  // Liberar recursos de la conexión
//     exit(0);
// }


// int key_hook(int keycode, void *param)
// {
//     t_game *game = (t_game *)param;

//     // printf("Key pressed: %d\n", keycode);  // Para verificar qué tecla fue presionada

//     if (keycode == 65307)  // Escape
//     {
//         close_game(game);
//         return(0);
//     }
//     else if (keycode == 65361)  // Flecha izquierda
//     {
//         move_player(game, -1, 0);
//         return(0);
//     }
//     else if (keycode == 65362)  // Flecha arriba
//     {
//         move_player(game, 0, -1);
//         return(0);
//     }
//     else if (keycode == 65363)  // Flecha derecha
//     {
//         move_player(game, 1, 0);
//         return(0);
//     }
//     else if (keycode == 65364)  // Flecha abajo
//     {
//         move_player(game, 0, 1);
//         return(0);
//     }
//     return (0);
// }


// int main(void)
// {
//     t_game game;

//     // Inicializar la estructura t_game
//     game.mlx = mlx_init();
//     game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "So_Long");

//     // Inicializar las posiciones del jugador y el mapa
//     game.player_x = 1;
//     game.player_y = 1;
//     game.map = map; // Aquí asignamos el mapa global a la estructura

//     draw_map(&game);  // Dibuja el mapa inicialmente

//     // Pasamos la estructura `game` al hook
//     mlx_key_hook(game.win, key_hook, &game);            // Gestionar teclas
//     mlx_hook(game.win, 17, 0, close_game, NULL);        // Gestionar "X"

//     mlx_loop(game.mlx);
//     return (0);
// }

//#############################################################################################//

// int	main(int argc, char **argv)
// {
// 	t_list	*d;

// 	if (argc != 2)
// 	{
// 		write(1, "Numero de argumentos incorrecto.\n", 33);
// 		return (0);
// 	}
// 	d = ft_calloc(1, sizeof(t_list));
// 	if (!d)
// 		return (0);
// 	d->mlx = mlx_init();
// 	init_data(d, argv[1]);
// 	mlx_key_hook(d->win, key_press, d);
// 	mlx_hook(d->win, 17, 0, ft_free, d);
// 	mlx_loop(d->mlx);
// 	ft_free(d);
// 	return (0);
// }

//#########################################################################################//

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		write(1, "Programme must be launch with 2 arguments.\n", 44);
// 		return (0);
// 	}
//     ber_extension_validation(argv[1]);
// 	return (0);
// }


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(1, "Programme must be launch with 2 arguments.\n", 44);
        printf("Uso: %s <archivo_mapa>\n", argv[0]);
        return 1;
    }
    if (!ber_extension_validation(argv[1]))
        exit(2);
    char **map = read_map(argv[1]);
    if (!map)
    {
        printf("Error al leer el mapa\n");
        return 1;
    }
    printf("Mapa cargado:\n");
    for (int i = 0; map[i] != NULL; i++)
        printf("%s", map[i]);
    printf("\n");
    free_map(map);
    return 0;
}
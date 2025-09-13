#include "minilibx-linux/mlx.h"

typedef struct  s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// int main(void)
// {
//     void    *mlx;
//     void    *mlx_win;
//     t_data  img;

//     // Inicializa MiniLibX y crea ventana
//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

//     // Crea imagen y obtiene dirección de píxeles
//     img.img = mlx_new_image(mlx, 1920, 1080);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

//     // Escribe un píxel rojo en (5,5)
//     my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
//     // Muestra imagen en la ventana
//     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

//     // Mantiene la ventana abierta
//     mlx_loop(mlx);
// }

#include <unistd.h>

int main(void)
{
    void    *mlx_win;
    void    *mlx;
    void    *img;
    char    *relative_path = "./test.xpm";
    int     img_width;
    int     img_height;

    mlx = mlx_init();
    if (!mlx)
        return (write(2, "Error: mlx_init falló\n", 23), (1));
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    if (!img)
        return (write(2, "Error: no se pudo cargar la imagen\n", 35), (1));
    mlx_win = mlx_new_window(mlx, 1334, 750, "Hello world!");
    if (!mlx_win)
        return (write(2, "Error: no se pudo crear la ventana\n", 36), (1));
    mlx_put_image_to_window(mlx, mlx_win, img, 670, 500);
    mlx_loop(mlx);
}


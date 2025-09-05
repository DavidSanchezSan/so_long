#include <stdio.h>

#define FILAS 4
#define COLUMNAS 5

// Definir los movimientos posibles: arriba, abajo, izquierda, derecha
int movX[] = {-1, 1, 0, 0};  // Cambios en las filas
int movY[] = {0, 0, -1, 1};  // Cambios en las columnas

// Función que verifica si las coordenadas están dentro del mapa
int es_valido(int x, int y, char grid[FILAS][COLUMNAS], int visitado[FILAS][COLUMNAS])
{
    return x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS && grid[x][y] != '1' && !visitado[x][y];
}

// DFS para verificar si podemos llegar a 'E' desde 'P', pasando por todas las 'C'
int dfs(int x, int y, char grid[FILAS][COLUMNAS], int visitado[FILAS][COLUMNAS], int total_colect, int total_c, int encontrado_E)
{
    int i;

    i = 0;
    // Si llegamos a 'E' y pasamos por todos los 'C'
    if (grid[x][y] == 'E')
    {
        if (total_colect == total_c)
        {
            encontrado_E = 1;
            return (1);
        }
        return (0);
    }
    // Marcar la celda como visitada
    visitado[x][y] = (1);
    // Si encontramos una 'C', contarla
    if (grid[x][y] == 'C')
        total_colect++;
    // Recorrer las celdas vecinas (arriba, abajo, izquierda, derecha)
    while(i < 4)
    {
        int nx = x + movX[i];
        int ny = y + movY[i];
        if (es_valido(nx, ny, grid, visitado))
        {
            if (dfs(nx, ny, grid, visitado, total_colect, total_c, encontrado_E))
            {
                return (1);
            }
        }
        i++;
    }
    // Si no encontramos el camino adecuado, desmarcar la celda y devolver falso
    visitado[x][y] = (0);
    return (0);
}

int main()
{
    // Cuadrícula con 'P' como punto de inicio, 'E' como punto de final, 'C' como colectables, '1' como muro y '0' como camino
    char grid[FILAS][COLUMNAS] =
    {
        {'P', '0', '0', '0', 'C'},
        {'0', '0', '0', '0', 'C'},
        {'0', 'C', '0', '0', 'E'},
        {'0', '0', '0', '0', '0'}
    };

    // Variables para el recorrido
    int startX = -1, startY = -1, endX = -1, endY = -1;
    int total_c = 0;  // Total de 'C' en el mapa

    // Contar cuántos 'C' hay y encontrar las posiciones de 'P' y 'E'
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (grid[i][j] == 'P') {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 'E') {
                endX = i;
                endY = j;
            } else if (grid[i][j] == 'C') {
                total_c++;
            }
        }
    }

    if (startX == -1 || endX == -1) {
        printf("No se encontraron los puntos de inicio o fin.\n");
        return 0;
    }

    // Inicializar el arreglo de visitados
    int visitado[FILAS][COLUMNAS] = {};

    int encontrado_E = 0;
    if (dfs(startX, startY, grid, visitado, 0, total_c, encontrado_E)) {
        if (encontrado_E) {
            printf("¡Se encontró un camino de 'P' a 'E' pasando por todos los 'C'!\n");
        }
    } else {
        printf("No hay camino posible de 'P' a 'E' pasando por todos los 'C'.\n");
    }

    return 0;
}

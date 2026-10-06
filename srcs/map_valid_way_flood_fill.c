/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_way.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:28:12 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/01 20:52:06 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Esta función guarda los valores x e y en la estructura stack en la
// posición indicada por stack->top y luego incrementa el índice top para
// apuntar al siguiente espacio disponible:
static void	push(t_stack *stack, int x, int y)
{
	stack->arr[stack->top].x = x;
	stack->arr[stack->top].y = y;
	stack->top++;
}

// Si la coordenada es visitable y no ha sido visitada es guardada en el stack.
static void	visit(char **map, t_stack *stack, int x, int y)
{
	if (map[y][x] != '1' && map[y][x] != 'V')
		push(stack, x, y);
}

// Inicializa pila de coord. con pos inicial.
static t_stack	*init_stack(int w, int h, int start_x, int start_y)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->arr = malloc(sizeof(t_coord) * (w * h));
	if (!stack->arr)
	{
		free(stack);
		return (NULL);
	}
	stack->top = 0;
	push(stack, start_x, start_y);
	return (stack);
}

// PRocesa una celda durante el flood_fill. Cuenta coleccionables,
// verifica si hay salida y marca como visitada la celda
static void	process_cell(char **map, t_coord cell, int *reach_c, int *reach_e)
{
	if (map[cell.y][cell.x] == 'C')
		(*reach_c)++;
	if (map[cell.y][cell.x] == 'E')
		*reach_e = 1;
	map[cell.y][cell.x] = 'V';
}

// Función flood fill desde una posición inicial en el mapa:
void	flood_fill(t_ff_params *p, int start_x, int start_y)
{
	t_stack	*stack;
	t_coord	cur;

	stack = init_stack(p->width, p->height, start_x, start_y);
	if (!stack)
		return ;
	while (stack->top > 0)
	{
		cur = stack->arr[--stack->top];
		if (p->data_map->map[cur.y][cur.x] == '1'
			|| p->data_map->map[cur.y][cur.x] == 'V')
			continue ;
		process_cell(p->data_map->map, cur, &p->reach_c, &p->reach_e);
		if (cur.x + 1 < p->width)
			visit(p->data_map->map, stack, cur.x + 1, cur.y);
		if (cur.x - 1 >= 0)
			visit(p->data_map->map, stack, cur.x - 1, cur.y);
		if (cur.y + 1 < p->height)
			visit(p->data_map->map, stack, cur.x, cur.y + 1);
		if (cur.y - 1 >= 0)
			visit(p->data_map->map, stack, cur.x, cur.y - 1);
	}
	free(stack->arr);
	free(stack);
}

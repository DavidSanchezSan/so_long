/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:07:19 by dasanche          #+#    #+#             */
/*   Updated: 2025/08/28 16:54:21 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**ber_map;
	t_map	map;
	int		i;

	i = 0;
	if (argc != 2)
	{
		print_error("Program must be launched with 2 arguments.\n");
		return (1);
	}
	if (!ber_extension_validation(argv[1]))
		exit (1);
	ber_map = read_map(argv[1]);
	if (!ber_map)
		return (2);
	map.objects = map_checks(ber_map);
	if (map.objects == 0)
		return(free_map(ber_map), (3));
	printf("Map objects: %i\n", map.objects);
	printf("Mapa cargado:\n");
	while (ber_map[i] != NULL)
	{
		printf("%s\n", ber_map[i]);
		i++;
	}
	printf("\n");
	free_map(ber_map);
	return (0);
}

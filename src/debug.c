/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:38:09 by marvin            #+#    #+#             */
/*   Updated: 2025/05/27 12:38:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	print_map_copy(char **map)
{
	int		y;

	y = 0;
	while (map && map[y])
	{
		printf("%s", map[y]);
		y++;
	}
}

void	print_map(t_map *map)
{
	int		y;

	y = 0;
	printf("\nMapa (%d x %d):\n", map->width, map->height);
	while (y < map->height)
	{
		printf("%s\n", map->complete_map[y]);
		y++;
	}
	printf("\n--- Texturas ---\n");
	printf("NO: %s\n", map->texture_no);
	printf("SO: %s\n", map->texture_so);
	printf("WE: %s\n", map->texture_we);
	printf("EA: %s\n", map->texture_ea);
	printf("\n--- Colores ---\n");
	printf("Floor:  0x%08X\n", map->color_floor);
	printf("Ceiling: 0x%08X\n\n", map->color_up);
}

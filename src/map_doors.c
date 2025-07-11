/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_doors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 08:17:05 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 11:40:55 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	count_doors(char **map)
{
	int		count;
	int		y;
	int		x;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	allocate_doors(t_game *game, int count)
{
	game->doors = malloc(sizeof(t_door) * count);
	if (!game->doors)
	{
		print_error("Error: malloc in doors.\n");
		exit(EXIT_FAILURE);
	}
	game->num_doors = count;
}

static void	fill_doors(t_game *game)
{
	int		x;
	int		y;
	int		i;

	y = 0;
	i = 0;
	while (game->map.complete_map[y])
	{
		x = 0;
		while (game->map.complete_map[y][x])
		{
			if (game->map.complete_map[y][x] == 'D')
			{
				game->doors[i].x = x;
				game->doors[i].y = y;
				game->doors[i].frame = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	detect_doors(t_game *game)
{
	int		count;

	count = count_doors(game->map.complete_map);
	allocate_doors(game, count);
	fill_doors(game);
}

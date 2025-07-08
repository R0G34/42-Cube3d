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

//20250706
// Cuenta el número de puertas para la estructura game
// main -> init_game_window -> detect_doors -> count_doors
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

//20250706
// Reserva memoria para las puertas
// main -> init_game_window -> detect_doors -> allocate_doors
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

//20250706
// Guarda la ubicación y el frame inicial (Que es 0 siempre)
// main -> init_game_window -> detect_doors -> fill_doors
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

//20250706
// Busca las puertas en el mapa y le dedica una estructura a cada una
// main -> init_game_window -> detect_doors
void	detect_doors(t_game *game)
{
	int		count;

	count = count_doors(game->map.complete_map);
	allocate_doors(game, count);
	fill_doors(game);
}

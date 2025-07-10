/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:40:47 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/10 21:22:43 by ajodar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250701
// El personaje actualiza su localización 
// main -> mlx_key_hook -> handle_key -> handle_movement
void	wall_collision(t_game *game)
{
	if (game->solid_walls == true)
	{
		game->solid_walls = false;
		printf("Solid wall: desactivated.\n");
	}
	else
	{
		game->solid_walls = true;
		printf("Solid wall: activated.\n");
	}
}

//20250701
// Comprueba que la casilla no tenga cerca null o espacios
// main -> mlx_key_hook -> handle_key -> handle_movement -> update_player_position -> is_inside_map -> is_surrounding_valid
static bool	is_valid_cell(t_map *map, int neighbor_y, int neighbor_x)
{
	if (neighbor_y < 0 || neighbor_y >= map->height)
		return (false);
	if (neighbor_x < 0 || neighbor_x >= \
	(int)ft_strlen(map->complete_map[neighbor_y]))
		return (false);
	return (map->complete_map[neighbor_y][neighbor_x] != ' ');
}

//20250701
// Comprueba que la casilla no tenga cerca null o espacios
// main -> mlx_key_hook -> handle_key -> handle_movement -> update_player_position -> is_inside_map
static bool	is_surroundings_valid(t_map *map, int mx, int my)
{
	int		dx;
	int		dy;
	int		row;

	dx = -2;
	while (dx <= 2)
	{
		dy = -2;
		while (dy <= 2)
		{
			row = my + dy;
			if (row < 0 || row >= map->height || !map->complete_map[row])
				return (false);
			if (!is_valid_cell(map, row, mx + dx))
				return (false);
			dy++;
		}
		dx++;
	}
	return (true);
}

//20250701
// Comprueba si la casilla actual es un suelo válido
// main -> mlx_key_hook -> handle_key -> handle_movement -> update_player_position -> is_inside_map
static bool	is_core_tile_open(t_map *map, int map_x, int map_y)
{
	int		row_len;

	if (map_y < 0 || map_y >= map->height)
		return (false);
	if (!map->complete_map[map_y])
		return (false);
	row_len = (int)ft_strlen(map->complete_map[map_y]);
	if (map_x < 0 || map_x >= row_len)
		return (false);
	return (map->complete_map[map_y][map_x] == '0');
}

//20250701
// Comprueba que la casilla a la que se dispone el personaje es válida
// main -> mlx_key_hook -> handle_key -> handle_movement -> update_player_position -> is_inside_map
bool	is_inside_map(t_map *map, double x, double y)
{
	int		mx;
	int		my;

	mx = (int)x;
	my = (int)y;
	if (is_core_tile_open(map, mx, my))
		return (true);
	if (mx < 2 || my < 2 || my >= map->height - 2)
		return (false);
	if (mx >= (int)ft_strlen(map->complete_map[my]) - 2)
		return (false);
	return (is_surroundings_valid(map, mx, my));
}


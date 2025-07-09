/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:40:47 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/09 10:02:49 by ajodar           ###   ########.fr       */
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
static bool	is_surroundings_valid(t_map *map, double x, double y)
{
	int		mx;
	int		my;
	int		dx;
	int		dy;
	int		row_len;

	mx = (int)x;
	my = (int)y;
	if (x < 1.1 || y < 1.1 || y > map->height - 1.1)
		return (false);
	row_len = (int)ft_strlen(map->complete_map[my]);
	if (x > row_len - 1.1)
		return (false);
	dy = -1;
	while (++dy <= 1)
	{
		dx = -1;
		while (++dx <= 1)
			if (!is_valid_cell(map, my + dy, mx + dx))
				return (false);
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
	int		map_x;
	int		map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (is_core_tile_open(map, map_x, map_y))
		return (true);
	return (is_surroundings_valid(map, x, y));
}

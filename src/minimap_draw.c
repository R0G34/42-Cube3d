/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:56:42 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/05 10:45:19 by ajodar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250703
// main -> draw_minimap -> draw_minimap_player -> draw_minimap_player_dot
static void	draw_minimap_player_dot(t_game *game, int px, int py)
{
	int		x;
	int		y;

	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			mlx_put_pixel(game->img, px + x, py + y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

//20250703
// main -> draw_minimap -> draw_minimap_player
static void	draw_minimap_player(t_game *game)
{
	int		px;
	int		py;
	int		dx;
	int		dy;

	px = (int)(game->player.x * MINIMAP_SCALE) + MINIMAP_OFFSET_X;
	py = (int)(game->player.y * MINIMAP_SCALE) + MINIMAP_OFFSET_Y;
	dx = (int)(game->player.dir_x * 5);
	dy = (int)(game->player.dir_y * 5);
	draw_minimap_player_dot(game, px, py);
	mlx_put_pixel(game->img, px + dx, py + dy, 0xFFFFFFFF);
}

//20250703
// main -> draw_minimap -> draw_minimap_tile
static void	draw_minimap_tile(t_game *game, int map_x, int map_y, uint32_t color)
{
	int		x;
	int		y;
	int		start_x;
	int		start_y;

	start_x = map_x * MINIMAP_SCALE + MINIMAP_OFFSET_X;
	start_y = map_y * MINIMAP_SCALE + MINIMAP_OFFSET_Y;
	y = 0;
	while (y < MINIMAP_SCALE)
	{
		x = 0;
		while (x < MINIMAP_SCALE)
		{
			mlx_put_pixel(game->img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

//20250703
// main -> draw_minimap
void	draw_minimap(void *param)
{
	t_game	*game = (t_game *)param;
	int		map_y;
	int		map_x;

	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < game->map.width)
		{
			char tile = game->map.complete_map[map_y][map_x];
			if (tile == '1')
				draw_minimap_tile(game, map_x, map_y, 0xFFFFFFFF);
			else
				draw_minimap_tile(game, map_x, map_y, game->map.color_floor);
			map_x++;
		}
		map_y++;
	}
	draw_minimap_player(game);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:17:56 by marvin            #+#    #+#             */
/*   Updated: 2025/05/27 11:17:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250527
// Inicia la pantallita de mlx y su ventana
// main -> init_game_window -> init_mlx
static void	init_mlx(t_game *game)
{
	int		minimap_height;
	int		total_height;

	minimap_height = game->map.height * MINIMAP_SCALE + 10;
	total_height = HEIGHT + minimap_height;
	game->mlx = mlx_init(WIDTH, total_height, "Terto3D", true);
	if (!game->mlx)
	{
		print_error("Error: mlx_init failed\n");
		exit(EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, total_height);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		print_error("Error: mlx_new_image failed\n");
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		mlx_terminate(game->mlx);
		print_error("Error: mlx_image_to_window failed\n");
		exit(EXIT_FAILURE);
	}
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
}

//20250527
// Busca los colores asignados y pinta el suelo y el cielo
// main -> init_game_window -> rc_setup -> init_background
// main -> render -> init_background (Cada vez que renderiza)
void	init_background(t_game *game)
{
	uint32_t	color;
	int			y;

	y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		if (y < HEIGHT / 2)
			color = game->map.color_up;
		else
			color = game->map.color_floor;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
}

//202500608
// main -> init_game_window
void	init_game_window(t_game *game, char *map_path)
{
	map_setup(&game->map, map_path);
	print_map(&game->map); // Debug temporal
	map_validate(&game->map);
	detect_doors(game);
	init_player(game);
	init_mlx(game);
	rc_setup(game);
}


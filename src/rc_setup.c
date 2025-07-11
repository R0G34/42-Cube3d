/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:40:13 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 11:47:51 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	load_door_textures(t_game *game)
{
	char	path[64];
	int		i;

	i = 0;
	while (i < 4)
	{
		build_texture_path(path, "./textures/doors/door", i, ".png");
		game->door[i] = mlx_load_png(path);
		if (!game->door[i])
		{
			print_error("Error: Failed loading door texture\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	load_wall_textures(t_game *game)
{
	game->tex_no = mlx_load_png(game->map.texture_no);
	game->tex_so = mlx_load_png(game->map.texture_so);
	game->tex_we = mlx_load_png(game->map.texture_we);
	game->tex_ea = mlx_load_png(game->map.texture_ea);
	if (!game->tex_no || !game->tex_so || !game->tex_we || !game->tex_ea)
	{
		print_error("Error: loading textures\n");
		exit(EXIT_FAILURE);
	}
}

void	rc_setup(t_game *game)
{
	load_wall_textures(game);
	load_door_textures(game);
	load_ui_frames(game);
	load_light_anim(game);
	init_background(game);
	game->solid_walls = true;
	game->is_running = false;
}

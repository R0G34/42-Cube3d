/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_load_frames.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:05:30 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 11:50:35 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	init_ui_anim_state(t_game *game)
{
	game->ui.frame_count = 4;
	game->ui.current_frame = 0;
	game->ui.is_animating = false;
}

static void	create_ui_image(t_game *game)
{
	int		x;
	int		y;

	game->ui.img = mlx_texture_to_image(game->mlx, game->ui.frames[0]);
	if (!game->ui.img)
	{
		print_error("Error: creating interface\n");
		exit(EXIT_FAILURE);
	}
	x = (WIDTH - game->ui.img->width) / 2;
	y = HEIGHT - game->ui.img->height;
	if (mlx_image_to_window(game->mlx, game->ui.img, x, y) == -1)
	{
		print_error("Error: creating interface\n");
		exit(EXIT_FAILURE);
	}
}

static void	load_ui_textures(t_game *game)
{
	int		i;
	char	*paths[4];

	paths[0] = "./textures/interface/frame0.png";
	paths[1] = "./textures/interface/frame1.png";
	paths[2] = "./textures/interface/frame2.png";
	paths[3] = "./textures/interface/frame3.png";
	i = 0;
	while (i < 4)
	{
		game->ui.frames[i] = mlx_load_png(paths[i]);
		if (!game->ui.frames[i])
		{
			print_error("Error: loading UI frame\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	load_ui_frames(t_game *game)
{
	load_ui_textures(game);
	create_ui_image(game);
	init_ui_anim_state(game);
}

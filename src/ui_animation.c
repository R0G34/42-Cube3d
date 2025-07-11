/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_animation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:17:55 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 11:48:49 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	ui_render_frame(t_game *game)
{
	int		x;
	int		y;

	mlx_delete_image(game->mlx, game->ui.img);
	game->ui.img = mlx_texture_to_image(game->mlx, \
		game->ui.frames[game->ui.current_frame]);
	if (!game->ui.img)
	{
		print_error("Error: can't animate interface\n");
		exit(EXIT_FAILURE);
	}
	x = (WIDTH - game->ui.img->width) / 2;
	y = HEIGHT - game->ui.img->height;
	if (mlx_image_to_window(game->mlx, game->ui.img, x, y) == -1)
	{
		print_error("Error: can't animate interface\n");
		exit(EXIT_FAILURE);
	}
}

void	ui_update(void *param)
{
	t_game		*game;
	static int	delay = 0;

	game = (t_game *)param;
	if (!game->ui.is_animating)
		return ;
	delay++;
	if (delay < UI_ANIM_DELAY)
		return ;
	delay = 0;
	game->ui.current_frame++;
	if (game->ui.current_frame >= game->ui.frame_count)
	{
		game->ui.is_animating = false;
		game->ui.current_frame = 0;
	}
	ui_render_frame(game);
}

void	start_ui_anim(t_game *game)
{
	if (!game->ui.is_animating)
	{
		game->ui.is_animating = true;
		game->ui.current_frame = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:58:42 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 11:50:17 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	render_light_frame(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (game->light.img)
		mlx_delete_image(game->mlx, game->light.img);
	game->light.img = mlx_texture_to_image(game->mlx, \
		game->light.frames[game->light.current_frame]);
	if (!game->light.img)
	{
		print_error("Error: creating light frame image\n");
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->light.img, x, y) == -1)
	{
		print_error("Error: displaying light frame\n");
		exit(EXIT_FAILURE);
	}
}

static void	load_light_textures(t_game *game)
{
	char	path[128];
	int		i;

	i = 0;
	while (i < 20)
	{
		build_texture_path(path, "textures/interface2/light", i + 1, ".png");
		game->light.frames[i] = mlx_load_png(path);
		if (!game->light.frames[i])
		{
			print_error("Error: loading light frame\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	light_update(void *param)
{
	t_game		*game;
	static int	delay = 0;

	game = (t_game *)param;
	if (game->light.finished)
		return ;
	delay++;
	if (delay < LIGHT_ANIM_DELAY)
		return ;
	delay = 0;
	game->light.current_frame++;
	if (game->light.current_frame >= 20)
	{
		game->light.current_frame = 19;
		game->light.finished = true;
	}
	render_light_frame(game);
}

static void	init_light_anim_state(t_game *game)
{
	game->light.current_frame = 0;
	game->light.finished = false;
}

void	load_light_anim(t_game *game)
{
	load_light_textures(game);
	init_light_anim_state(game);
	render_light_frame(game);
}

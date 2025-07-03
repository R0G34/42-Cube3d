/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:58:22 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/03 21:03:27 by ajodar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);

	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

void	recenter_mouse(void *param)
{
	t_game *game = (t_game *)param;

	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
}

void	handle_mouse_rotation(double xpos, double ypos, void *param)
{
	(void)ypos; // evitar warning
	t_game *game = (t_game *)param;
	static double last_x;
	double delta_x;
	double sensitivity;

	last_x = WIDTH / 2;
	sensitivity = 0.0003;
	delta_x = xpos - last_x;
	if (delta_x != 0)
		rotate_player(game, delta_x * sensitivity);
}





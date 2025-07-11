/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 09:33:05 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 14:37:23 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	update_player_position(t_game *game, double next_x, double next_y)
{
	if (game->solid_walls)
	{
		if (is_inside_map(&game->map, game->player.x, next_y) &&
			game->map.complete_map[(int)next_y][(int)game->player.x] != '1')
		{
			game->player.y = next_y;
		}
		if (is_inside_map(&game->map, next_x, game->player.y) &&
			game->map.complete_map[(int)game->player.y][(int)next_x] != '1')
		{
			game->player.x = next_x;
		}
	}
	else
	{
		if (is_inside_map(&game->map, next_x, game->player.y))
			game->player.x = next_x;
		if (is_inside_map(&game->map, game->player.x, next_y))
			game->player.y = next_y;
	}
}

void	handle_movement(t_game *game, mlx_key_data_t keydata, double move_speed)
{
	double		next_x;
	double		next_y;

	next_x = game->player.x;
	next_y = game->player.y;
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
	{
		next_x += game->player.dir_x * move_speed;
		next_y += game->player.dir_y * move_speed;
	}
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
	{
		next_x -= game->player.dir_x * move_speed;
		next_y -= game->player.dir_y * move_speed;
	}
	else
		return ;
	update_player_position(game, next_x, next_y);
	start_ui_anim(game);
}

static void	rotate_player(t_game *game, double rot_speed)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed) - \
		game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + \
		game->player.dir_y * cos(rot_speed);
	game->player.plane_x = game->player.plane_x * cos(rot_speed) - \
		game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + \
		game->player.plane_y * cos(rot_speed);
}

void	handle_rotation(t_game *game, mlx_key_data_t keydata)
{
	double		rot_speed;

	rot_speed = ROT_SPEED;
	if (keydata.key == MLX_KEY_E || keydata.key == MLX_KEY_RIGHT)
		rotate_player(game, rot_speed);
	else if (keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_LEFT)
		rotate_player(game, -rot_speed);
	start_ui_anim(game);
}

void	handle_lateral(t_game *game, mlx_key_data_t keydata, double move_speed)
{
	double	side_x;
	double	side_y;
	double	next_x;
	double	next_y;

	side_x = 0;
	side_y = 0;
	if (keydata.key == MLX_KEY_D)
	{
		side_x = -game->player.dir_y;
		side_y = game->player.dir_x;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		side_x = game->player.dir_y;
		side_y = -game->player.dir_x;
	}
	else
		return ;
	next_x = game->player.x + side_x * move_speed;
	next_y = game->player.y + side_y * move_speed;
	update_player_position(game, next_x, next_y);
	start_ui_anim(game);
}

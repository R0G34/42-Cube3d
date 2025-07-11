/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:17:52 by marvin            #+#    #+#             */
/*   Updated: 2025/05/27 11:17:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	init_game_window(&game, argv[1]);
	mlx_key_hook(game.mlx, handle_key, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop_hook(game.mlx, ui_update, &game);
	mlx_loop_hook(game.mlx, light_update, &game);
	mlx_loop_hook(game.mlx, draw_minimap, &game);
	mlx_loop_hook(game.mlx, update_doors, &game);
	mlx_loop_hook(game.mlx, recenter_mouse, &game);
	mlx_cursor_hook(game.mlx, handle_mouse_rotation, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}

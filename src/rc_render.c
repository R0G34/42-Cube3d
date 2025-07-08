/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:39:59 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 11:47:36 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250608
// main -> render -> cast_ray -> init_ray_direction
static void	init_ray_direction(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->delta_dist_x = ft_fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = ft_fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

//20250608
// main -> render -> cast_ray -> init_ray_steps
static void	init_ray_steps(t_ray *ray, t_game *game)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) \
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) \
			* ray->delta_dist_y;
	}
}

//20250608
// Gestiona dda cuando se trata de una puerta
// main -> render -> cast_ray -> perform_dda -> perform_dda_doors
static bool	perform_dda_doors(t_ray *ray, t_game *game)
{
	int			i;
	t_door		*door;

	i = 0;
	while (i < game->num_doors)
	{
		door = &game->doors[i];
		if (door->x == ray->map_x && door->y == ray->map_y)
		{
			if (door->frame < 3)
				return (true);
			return (false);
		}
		i++;
	}
	return (false);
}

//20250608
// Hace el calculo que detecta la colisión con las paredes
// main -> render -> cast_ray -> perform_dda
void	perform_dda(t_ray *ray, t_game *game)
{
	char	tile;

	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		tile = game->map.complete_map[ray->map_y][ray->map_x];
		if (tile == '1')
			ray->hit = 1;
		else if (tile == 'D' && perform_dda_doors(ray, game))
			ray->hit = 1;
	}
}

//20250706
// main -> render
void	render(void *param)
{
	t_game	*game;
	t_ray	ray;
	int		x;

	game = (t_game *)param;
	init_background(game);
	x = 0;
	while (x < WIDTH)
	{
		init_ray_direction(&ray, game, x);
		init_ray_steps(&ray, game);
		perform_dda(&ray, game);
		draw_column(game, x, &ray);
		x++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:55:58 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 11:46:58 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	compute_texture_x(t_game *game, t_ray *ray, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static mlx_texture_t	*get_door_texture(t_game *game, int map_x, int map_y)
{
	int		j;

	j = 0;
	while (j < game->num_doors)
	{
		if (game->doors[j].x == map_x && game->doors[j].y == map_y)
		{
			if (game->doors[j].frame == 3)
				return (NULL);
			return (game->door[game->doors[j].frame]);
		}
		j++;
	}
	return (NULL);
}

static mlx_texture_t	*select_texture(t_game *game, t_ray *ray)
{
	char			tile;
	mlx_texture_t	*door_tex;

	tile = game->map.complete_map[ray->map_y][ray->map_x];
	if (tile == 'D')
	{
		door_tex = get_door_texture(game, ray->map_x, ray->map_y);
		if (door_tex)
			return (door_tex);
	}
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return (game->tex_we);
		else
			return (game->tex_ea);
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return (game->tex_no);
		else
			return (game->tex_so);
	}
}

static void	compute_projection(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x + \
			(1 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y + \
			(1 - ray->step_y) / 2.0) / ray->ray_dir_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	draw_column(t_game *game, int x, t_ray *ray)
{
	mlx_texture_t	*tex;
	int				tex_x;
	t_column_info	col;

	compute_projection(game, ray);
	tex = select_texture(game, ray);
	if (!tex || !tex->pixels)
		return ;
	tex_x = compute_texture_x(game, ray, tex);
	if (tex_x < 0 || tex_x >= (int)tex->width)
		return ;
	col.x = x;
	col.tex_x = tex_x;
	render_textured_column(game, ray, tex, col);
}

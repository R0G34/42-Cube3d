/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:16:49 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 12:04:39 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	draw_texture_pixel(t_game *game, mlx_texture_t *tex, \
t_tex_render_data *data, int y)
{
	int			tex_y;
	uint8_t		*pixel;
	uint32_t	color;

	tex_y = (int)data->tex_pos;
	if (tex_y >= 0 && tex_y < (int)tex->height)
	{
		pixel = &tex->pixels[4 * (tex_y * tex->width + data->tex_x)];
		color = (pixel[0] << 24) | (pixel[1] << 16) | \
			(pixel[2] << 8) | pixel[3];
		mlx_put_pixel(game->img, data->x, y, color);
	}
}

static void	compute_texture_step(t_ray *ray, mlx_texture_t *tex, \
double *tex_step, double *tex_pos)
{
	*tex_step = (double)tex->height / ray->line_height;
	*tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) \
		* (*tex_step);
}

static void	draw_column_loop(t_game *game, t_ray *ray, mlx_texture_t *tex, \
t_tex_render_data *data)
{
	int		y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		draw_texture_pixel(game, tex, data, y);
		data->tex_pos += data->tex_step;
		y++;
	}
}

void	render_textured_column(t_game *game, t_ray *ray, mlx_texture_t *tex,
								t_column_info col)
{
	t_tex_render_data	data;

	compute_texture_step(ray, tex, &data.tex_step, &data.tex_pos);
	data.x = col.x;
	data.tex_x = col.tex_x;
	draw_column_loop(game, ray, tex, &data);
}

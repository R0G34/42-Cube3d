/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:13:42 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 12:21:39 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "define.h"
# include "MLX42/MLX42.h"

typedef struct s_map
{
	char		*texture_no;
	char		*texture_so;
	char		*texture_we;
	char		*texture_ea;
	uint32_t	color_floor;
	uint32_t	color_up;
	char		**complete_map;
	int			width;
	int			height;
}	t_map;

typedef struct s_flood_state
{
	int	*count;
	int	*valid;
}	t_floo_state;

typedef struct s_column_info
{
	int	x;
	int	tex_x;
}	t_column_info;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ui_anim
{
	mlx_texture_t	*frames[4];
	mlx_image_t		*img;
	int				frame_count;
	int				current_frame;
	bool			is_animating;
}	t_ui_anim;

typedef struct s_light_anim
{
	mlx_texture_t	*frames[20];
	mlx_image_t		*img;
	int				current_frame;
	bool			finished;
}	t_light_anim;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	int		map_x;
	int		map_y;

	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;

	int		step_x;
	int		step_y;

	int		hit;
	int		side;

	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_tex_render_data
{
	double		tex_step;
	double		tex_pos;
	int			x;
	int			tex_x;
}	t_tex_render_data;

typedef struct s_door
{
	int		x;
	int		y;
	int		frame;
}	t_door;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			map;
	t_player		player;
	bool			solid_walls;
	bool			is_running;
	mlx_texture_t	*tex_no;
	mlx_texture_t	*tex_so;
	mlx_texture_t	*tex_we;
	mlx_texture_t	*tex_ea;
	mlx_texture_t	*door[4];
	t_door			*doors;
	int				num_doors;
	t_ui_anim		ui;
	t_light_anim	light;
}	t_game;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:18:18 by marvin            #+#    #+#             */
/*   Updated: 2025/05/27 11:18:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "MLX42/MLX42.h"
# include "define.h"
# include "struct.h"
# include "../src/libft/libft.h"
# include "../src/get_next_line/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

// Basic
# define WIDTH 800
# define HEIGHT 600

// Init
void		init_game_window(t_game *game, char *map_path);
void		init_map(t_map *map);
int			map_setup(t_map *map, char *map_name);
void		init_player(t_game *game);
void		init_background(t_game *game);

// Cleanup
void		cleanup_game(t_game *game);
void		free_map_copy(char **map_copy);

// Parsing y validation
int			map_parse(t_map *map, char *map_path);
uint32_t	parse_rgb(const char *str);
int			parse_texture_colors(t_map *map, char *line);
int			map_validate(t_map *map);
int			validate_walls(char **map, int start_x, int start_y);
int			validate_colors_and_textures(t_map *map);
int			prevalidate_map_file(const char *filepath);
void		detect_doors(t_game *game);

// Raycasting
void		rc_setup(t_game *game);
void		perform_dda(t_ray *ray, t_game *game);
void		draw_column(t_game *game, int x, t_ray *ray);
void		render(void *param);
void	render_textured_column(t_game *game, t_ray *ray, mlx_texture_t *tex,
								t_column_info col);
void		draw_minimap(void *param);
void		update_doors(void *param);

// Input
void		handle_key(mlx_key_data_t keydata, void *param);
void		handle_mouse_rotation(double xpos, double ypos, void *param);
void		recenter_mouse(void *param);

// Move
void		handle_lateral(t_game *game, mlx_key_data_t keydata, \
double move_speed);
void		handle_rotation(t_game *game, mlx_key_data_t keydata);
void		handle_movement(t_game *game, mlx_key_data_t keydata, \
double move_speed);
void		update_player_position(t_game *game, double next_x, double next_y);

// UI
void		load_ui_frames(t_game *game);
void		ui_update(void *param);
void		start_ui_anim(t_game *game);

// Light
void		load_light_anim(t_game *game);
void		light_update(void *param);
void		render_light_frame(t_game *game);
void		restart_light_anim(t_game *game);

// Debug (Borrar luego)
void		print_map(t_map *map);
void		print_map_copy(char **map);

// Hotkeys
void		wall_collision(t_game *game);
bool		is_inside_map(t_map *map, double x, double y);

// Utils
int			ft_abs(int n);
double		ft_fabs(double n);
void		print_error(const char *format);
void		build_texture_path(char *dest, const char *base, int index, \
const char *ext);

#endif

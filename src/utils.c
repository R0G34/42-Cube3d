/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 10:42:24 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 12:34:30 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250706
// main -> update_doors -> ft_abs
int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

//20250706
// main -> render -> cast_ray -> init_ray_direction
double	ft_fabs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

//20250706
// main -> init_game_window -> rc_setup -> load_ui_frames -> load_ui_textures
// main -> init_game_window -> rc_setup -> load_ui_frames -> create_ui_image
// main -> init_game_window -> rc_setup -> load_ligth_anim -> load_ligth_textures
// main -> init_game_window -> rc_setup -> load_ligth_anim -> render_ligth_frame
// main -> init_game_window -> rc_setup -> load_wall_textures
// main -> init_game_window -> rc_setup -> load_door_textures
// main -> init_game_window -> map_setup -> prevalidate_map_file
// main -> init_game_window -> map_validate -> validate_wallsclear
// main -> init_game_window -> detect_doors -> allocate_doors
// main -> init_game_window -> init_mlx
// main -> mlx_loop_hook -> ui_update -> ui_render_frame
void	print_error(const char *msg)
{
	while (*msg)
		write(2, msg++, 1);
}

//202850706
// Para concatenar numeros a las rutas de las texturas
// main -> init_game_window -> rc_setup -> load_ligth_anim -> load_ligth_textures
// main -> init_game_window -> rc_setup -> load_door_textures
void	build_texture_path(char *dest, const char *base, int index, \
	const char *ext)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (base[i])
	{
		dest[i] = base[i];
		i++;
	}
	if (index >= 10)
		dest[i++] = '0' + (index / 10);
	dest[i++] = '0' + (index % 10);
	while (ext[j])
		dest[i++] = ext[j++];
	dest[i] = '\0';
}

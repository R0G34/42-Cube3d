/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:35:41 by marvin            #+#    #+#             */
/*   Updated: 2025/05/28 10:35:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	free_map_copy(char **map_copy)
{
	int		i;

	i = 0;
	if (!map_copy)
		return ;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->complete_map)
	{
		while (map->complete_map[i])
		{
			free(map->complete_map[i]);
			i++;
		}
		free(map->complete_map);
	}
	free(map->texture_no);
	free(map->texture_so);
	free(map->texture_we);
	free(map->texture_ea);
}

static void	delete_texture_array(mlx_texture_t **textures, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		if (textures[i])
			mlx_delete_texture(textures[i]);
		i++;
	}
}

void	cleanup_game(t_game *game)
{
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	free_map(&game->map);
	if (game->tex_no)
		mlx_delete_texture(game->tex_no);
	if (game->tex_so)
		mlx_delete_texture(game->tex_so);
	if (game->tex_we)
		mlx_delete_texture(game->tex_we);
	if (game->tex_ea)
		mlx_delete_texture(game->tex_ea);
	delete_texture_array(game->ui.frames, game->ui.frame_count);
	if (game->ui.img)
		mlx_delete_image(game->mlx, game->ui.img);
	delete_texture_array(game->light.frames, 20);
	if (game->light.img)
		mlx_delete_image(game->mlx, game->light.img);
	delete_texture_array(game->door, 4);
	if (game->doors)
		free(game->doors);
}

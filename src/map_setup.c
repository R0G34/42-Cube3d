/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:03:45 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/06 10:31:10 by ajodar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250604
// Limpia lo que tenga la estructura de mapa antes de usarla
// main -> init_game_window -> map_setup -> init_map
void	init_map(t_map *map)
{
	map->texture_no = NULL;
	map->texture_so = NULL;
	map->texture_we = NULL;
	map->texture_ea = NULL;
	map->color_floor = 0xFFFFFFFF;
	map->color_up = 0xFFFFFFFF;
	map->complete_map = NULL;
	map->width = 0;
	map->height = 0;
}

//20250607
// Valida la ruta del mapa
// main -> init_game_window -> map_setup -> validate_map_path
static int	validate_map_path(const char *path)
{
	int		len;
	int		fd;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
	{
		printf("Error: map dont have extension .cub\n");
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: open the map");
		return (1);
	}
	close(fd);
	return (0);
}

//20250706
// Calcula y devuelve dinámicamente la ruta completa
// main -> init_game_window -> map_setup -> build_map_path
static char	*build_map_path(const char *filename)
{
	size_t		len;
	char		*path;

	len = ft_strlen("maps/") + ft_strlen(filename) + 1;
	path = malloc(len);
	if (!path)
		return (NULL);
	ft_strlcpy(path, "maps/", len);
	ft_strlcat(path, filename, len);
	return (path);
}

//20250706
// Crea la ruta completa al mapa, valida y parsea todo a la estructura map
// main -> init_game_window -> map_setup
int	map_setup(t_map *map, char *map_name)
{
	char	*full_path;

	full_path = build_map_path(map_name);
	if (!full_path)
		exit(EXIT_FAILURE);
	if (validate_map_path(full_path) != 0)
	{
		free(full_path);
		exit(EXIT_FAILURE);
	}
	if (prevalidate_map_file(full_path) != 0)
	{
		free(full_path);
		exit(EXIT_FAILURE);
	}
	if (map_parse(map, full_path) != 0)
	{
		free(full_path);
		exit(EXIT_FAILURE);
	}
	free(full_path);
	return (0);
}

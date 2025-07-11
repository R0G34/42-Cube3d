/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:22:05 by marvin            #+#    #+#             */
/*   Updated: 2025/06/03 09:22:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	is_header_line(const char *line)
{
	return (
		ft_strncmp(line, "NO ", 3) == 0 || \
		ft_strncmp(line, "SO ", 3) == 0 || \
		ft_strncmp(line, "WE ", 3) == 0 || \
		ft_strncmp(line, "EA ", 3) == 0 || \
		ft_strncmp(line, "F ", 2) == 0 || \
		ft_strncmp(line, "C ", 2) == 0 || \
		line[0] == '\n'
	);
}

static int	is_valid_map_line(const char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		c = line[i];
		if (c == '\r')
		{
			i++;
			continue ;
		}
		if (!(c == '0' || c == '1' || c == 'N' || c == 'S' || \
			c == 'E' || c == 'W' || c == 'D' || c == ' '))
		{
			print_error("Error: Invalid char");
			return (0);
		}
		i++;
	}
	return (1);
}

int	prevalidate_map_file(const char *filepath)
{
	int		fd;
	char	*line;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	while ((line = get_next_line(fd)))
	{
		if (is_header_line(line))
		{
			free(line);
			continue ;
		}
		if (!is_valid_map_line(line))
		{
			print_error("Error: Invalid character in map.\n");
			free(line);
			close(fd);
			return (1);
		}
		free(line);
	}
	close(fd);
	return (0);
}

int	validate_player_start(char **map, int *x, int *y)
{
	int		i;
	int		j;
	int		found;

	i = 0;
	found = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				*x = j;
				*y = i;
				found++;
			}
			j++;
		}
		i++;
	}
	if (found != 1)
		return (print_error("Error: player not correct\n"), 1);
	return (0);
}

int	map_validate(t_map *map)
{
	int		start_x;
	int		start_y;

	if (validate_colors_and_textures(map) != 0)
		exit(EXIT_FAILURE);
	if (validate_player_start(map->complete_map, &start_x, &start_y) != 0)
		exit(EXIT_FAILURE);
	if (validate_walls(map->complete_map, start_x, start_y) != 0)
		exit(EXIT_FAILURE);
	return (0);
}

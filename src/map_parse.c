/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parseo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:18:30 by marvin            #+#    #+#             */
/*   Updated: 2025/05/27 12:18:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static char	*sanitize_line(const char *src, int width)
{
	int		i;
	char	c;
	char	*dst;

	dst = malloc(width + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] && i < width)
	{
		c = src[i];
		if (c == '0' || c == '1' || c == 'N' || c == 'S' || \
			c == 'E' || c == 'W' || c == 'D' || c == ' ')
			dst[i] = c;
		else
			dst[i] = ' ';
		i++;
	}
	while (i < width)
		dst[i++] = ' ';
	dst[i] = '\0';
	return (dst);
}

static void	pad_map_lines(char **map_lines, int total_lines, int width)
{
	char	*clean;
	int		i;

	i = 0;
	while (i < total_lines)
	{
		clean = sanitize_line(map_lines[i], width);
		if (!clean)
			return ;
		free(map_lines[i]);
		map_lines[i] = clean;
		i++;
	}
}

static int	is_valid_map_line(const char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	if (*line == '1' || *line == '0' || *line == 'N' || *line == 'S' || \
		*line == 'E' || *line == 'W')
		return (1);
	return (0);
}

static char **extract_textures_colors_maps(t_map *map, int *width, int *map_lines, int fd)
{
	char	*line;
	char	**tmp_map;
	size_t	len;

	tmp_map = malloc(sizeof(char *) * 1024);
	if (!tmp_map)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (parse_texture_colors(map, line) || !is_valid_map_line(line))
			free(line);
		else
		{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
			if ((int)len > *width)
				*width = len;
			tmp_map[(*map_lines)++] = line;
		}
	}
	return (tmp_map);
}

int	map_parse(t_map *map, char *map_path)
{
	int			fd;
	char		**tmp_map;
	int			map_lines;
	int			width;

	map_lines = 0;
	width = 0;
	init_map(map);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), -1);
	tmp_map = extract_textures_colors_maps(map, &width, &map_lines, fd);
	if (!tmp_map)
		return (close(fd), -1);
	pad_map_lines(tmp_map, map_lines, width);
	tmp_map[map_lines] = NULL;
	map->complete_map = tmp_map;
	map->height = map_lines;
	map->width = width;
	close(fd);
	return (0);
}


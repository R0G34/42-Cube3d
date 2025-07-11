/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:47:16 by marvin            #+#    #+#             */
/*   Updated: 2025/06/03 09:47:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250603
// Duplica el mapa sobre el que vamos a revisar la validación con floodfill
// main -> init_game_window -> map_validate -> validate_walls -> duplicate_map
static char	**duplicate_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

//20250706
// Pequeña función para dividir flood_check
// main -> init_game_window -> map_validate -> validate_walls -> flood_check -> is_invalid_tile
static int	is_invalid_tile(char c)
{
	return (c != '0' && c != 'N' && c != 'S' && \
		c != 'E' && c != 'W' && c != 'D');
}

//20250603
// Realiza un floodfill sobre el mapa para ver fugas
// main -> init_game_window -> map_validate -> validate_walls -> flood_check
static void	flood_check(char **map, int x, int y, t_flood_state *state)
{
	if (y < 0 || map[y] == NULL || x < 0 || x >= (int)ft_strlen(map[y]))
	{
		*(state->valid) = 1;
		return ;
	}
	if (*(state->count) >= 4000 || *(state->valid) != 0)
		return ;
	(*(state->count))++;
	if (map[y][x] == ' ' || map[y][x] == '\0')
	{
		*(state->valid) = 1;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	if (is_invalid_tile(map[y][x]))
	{
		*(state->valid) = 1;
		return ;
	}
	map[y][x] = 'V';
	flood_check(map, x + 1, y, state);
	flood_check(map, x - 1, y, state);
	flood_check(map, x, y + 1, state);
	flood_check(map, x, y - 1, state);
}

//20250603
// Valida que los muros cierren lanzando un floodfill desde dentro
// main -> init_game_window -> map_validate -> validate_walls
int	validate_walls(char **map, int start_x, int start_y)
{
	char			**map_copy;
	int				valid;
	int				count;
	t_flood_state	state;

	count = 0;
	valid = 0;
	state.count = &count;
	state.valid = &valid;
	map_copy = duplicate_map(map);
	if (!map_copy)
	{
		print_error("Error: Failed to duplicate the map for validation.\n");
		return (1);
	}
	flood_check(map_copy, start_x, start_y, &state);
	free_map_copy(map_copy);
	if (valid != 0 || count < 5 || count > 3999)
	{
		print_error("Error: Map is not valid.\n");
		return (1);
	}
	return (0);
}

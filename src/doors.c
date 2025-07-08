/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar-c <ajodar-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 08:50:29 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/08 14:29:07 by ajodar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250706
// Actualiza el estado de las puertas cuando el personaje está cerca
// main -> update_doors -> should_update_doors
static bool	should_update_doors(void)
{
	static int	frame_skip = 0;

	frame_skip++;
	if (frame_skip < DOORS_DELAY)
		return (false);
	frame_skip = 0;
	return (true);
}

//20250708
// Actualiza el frame de una puerta
// main -> update_doors -> update_one_door
static void	update_one_door(t_game *game, t_door *door)
{
	int		dx;
	int		dy;

	dx = ft_abs((int)game->player.x - door->x);
	dy = ft_abs((int)game->player.y - door->y);
	if ((dx <= 1 && dy <= 0) || (dy <= 1 && dx <= 0))
	{
		if (door->frame < 3)
			door->frame++;
	}
	else
	{
		if (door->frame > 0)
			door->frame--;
	}
}

//20250708
// Actualiza el estado de las puertas cuando el personaje está cerca
// main -> update_doors
void	update_doors(void *param)
{
	t_game		*game;
	int			i;

	game = (t_game *)param;
	if (!should_update_doors())
		return ;
	i = 0;
	while (i < game->num_doors)
	{
		update_one_door(game, &game->doors[i]);
		i++;
	}
}


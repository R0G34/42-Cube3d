/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:04:30 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/01 13:11:56 by ajodar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	restart_light_anim(t_game *game)
{
	game->light.current_frame = 0;
	game->light.finished = false;
	render_light_frame(game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:00:11 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/06 09:42:35 by ajodar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// Dimensiones de la pantalla
# define WIDTH 800
# define HEIGHT 600
# define FOV 260.0

// Movement & Rotation
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

// Animación de UI
# define UI_ANIM_DELAY 10

// Animación de luz
# define LIGHT_FRAME_COUNT 20
# define LIGHT_ANIM_DELAY 600

// Animación de las puertas
# define DOORS_DELAY 5

// Minimap
# define MINIMAP_SCALE 6
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y (HEIGHT + 10)

#endif

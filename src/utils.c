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

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

double	ft_fabs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	print_error(const char *msg)
{
	while (*msg)
		write(2, msg++, 1);
}

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

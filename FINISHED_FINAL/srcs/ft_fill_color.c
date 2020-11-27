/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:31:24 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:50:12 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_fill_color(char **array, t_cub *scene, char id)
{
	int	a;
	int r;
	int g;
	int b;

	a = 0;
	r = ft_atoi(array[0]);
	g = ft_atoi(array[1]);
	b = ft_atoi(array[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	if (id == 'F')
		scene->floor_color = (a << 24) | (r << 16) | (g << 8) | b;
	if (id == 'C')
		scene->ceiling_color = (a << 24) | (r << 16) | (g << 8) | b;
	return (1);
}

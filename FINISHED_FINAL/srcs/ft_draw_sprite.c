/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:24:18 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:27:41 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_sprite(int x, double dist, t_cub *scene, double dist_arr[])
{
	int		i;
	int		j;
	int		y;

	ft_set_size_skip_neg(&j, &x, dist, scene);
	while (j < 64 && scene->kj < scene->size && x < scene->res_x)
	{
		y = scene->res_y / 2 - scene->size / 2;
		scene->ki = 0;
		i = (int)(scene->ki / scene->scale);
		while (i < 64 && scene->ki < scene->size && y < scene->res_y)
		{
			scene->color = *((unsigned int *)(scene->addr_sprite + \
				(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
			if (dist < dist_arr[x])
				ft_paint_sprite(x, y, scene);
			y++;
			scene->ki++;
			i = (int)(scene->ki / scene->scale);
		}
		x++;
		scene->kj++;
		j = (int)(scene->kj / scene->scale);
	}
}

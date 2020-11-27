/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:00:13 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:10:23 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_wall(int x, int *ry, t_cub *scene)
{
	int i;
	int j;
	int y;

	i = (int)(scene->ki / scene->scale);
	j = scene->offset;
	y = *ry;
	while (i < 64 && scene->ki < scene->size && y < scene->res_y)
	{
		scene->color = *((unsigned int *)(scene->texture + \
				(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
		if (scene->save_flag == 1)
			scene->array[y][x] = scene->color;
		else
			ft_my_pixel_put(scene, x, y, scene->color);
		y++;
		scene->ki++;
		i = (int)(scene->ki / scene->scale);
	}
	*ry = y;
}

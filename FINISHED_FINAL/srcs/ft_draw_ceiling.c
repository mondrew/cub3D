/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_ceiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:59:47 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:09:44 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_ceiling(int x, int y, t_cub *scene)
{
	int ny;

	ny = 0;
	if (y < 0)
		return ;
	while (ny < y)
	{
		if (scene->save_flag == 1)
			scene->array[ny][x] = scene->ceiling_color;
		else
			ft_my_pixel_put(scene, x, ny, scene->ceiling_color);
		ny++;
	}
}

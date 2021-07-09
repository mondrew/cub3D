/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:00:02 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:10:02 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_floor(int x, int y, t_cub *scene)
{
	while (y < scene->res_y)
	{
		if (scene->save_flag == 1)
			scene->array[y][x] = scene->floor_color;
		else
			ft_my_pixel_put(scene, x, y, scene->floor_color);
		y++;
	}
}

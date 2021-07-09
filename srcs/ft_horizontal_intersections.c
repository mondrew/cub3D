/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_horizontal_intersictions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:03:00 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/14 10:28:44 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_horizontal_intersections(t_cub *scene)
{
	if (scene->dir_y != 0)
	{
		if (scene->dir_y < 0)
			scene->hi_y = ((int)(scene->plr_glb_y / 64)) * 64 - 0.0001;
		if (scene->dir_y > 0)
			scene->hi_y = ((int)(scene->plr_glb_y / 64)) * 64 + 64;
		scene->ray_map_y = scene->hi_y / 64;
		scene->hi_x = scene->plr_glb_x + \
			(scene->plr_glb_y - scene->hi_y) / tan(scene->ray_angle);
		scene->ray_map_x = scene->hi_x / 64;
		while (ft_check_coord(scene) != 0 && ft_check_wall_sprite(scene) != 1)
		{
			scene->hi_x = scene->hi_x + scene->hi_dx;
			scene->hi_y = scene->hi_y + scene->hi_dy;
			scene->ray_map_x = scene->hi_x / 64;
			scene->ray_map_y = scene->hi_y / 64;
		}
		scene->line_len_h = ft_line_len(scene->hi_y, scene->hi_x, scene);
	}
	else
		scene->line_len_h = 0;
}

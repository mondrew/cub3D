/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hor_inter_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:25:00 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:28:41 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hor_inter_sprite(int *i, t_sprite sprite[], t_cub *scene)
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
			ft_add_sprite_data(i, sprite, scene);
			scene->hi_x = scene->hi_x + scene->hi_dx;
			scene->hi_y = scene->hi_y + scene->hi_dy;
			scene->ray_map_x = scene->hi_x / 64;
			scene->ray_map_y = scene->hi_y / 64;
		}
	}
}

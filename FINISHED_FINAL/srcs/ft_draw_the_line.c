/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_the_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:01:15 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:11:22 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_draw_the_line(int x, t_cub *scene)
{
	int		y;

	ft_set_size(scene);
	y = ft_get_real_y(scene);
	ft_draw_ceiling(x, y, scene);
	if (scene->line_len_h < scene->line_len_v)
	{
		if (scene->dir_y >= 0)
			scene->texture = scene->addr_no_tex;
		if (scene->dir_y < 0)
			scene->texture = scene->addr_so_tex;
	}
	if (scene->line_len_h > scene->line_len_v)
	{
		if (scene->dir_x >= 0)
			scene->texture = scene->addr_ea_tex;
		if (scene->dir_x < 0)
			scene->texture = scene->addr_we_tex;
	}
	ft_draw_wall(x, &y, scene);
	ft_draw_floor(x, y, scene);
	return (0);
}

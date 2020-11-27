/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:23:57 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:27:13 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_paint_sprite(int x, int y, t_cub *scene)
{
	if (scene->save_flag == 1 && scene->color != 0x00000000)
		scene->array[y][x] = scene->color;
	else if (scene->color != 0x00000000)
		ft_my_pixel_put(scene, x, y, scene->color);
}

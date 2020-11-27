/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_pixel_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 20:34:42 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/21 22:13:53 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_my_pixel_put(t_cub *scene, int x, int y, int color)
{
	char	*dst;

	dst = scene->addr + (y * scene->size_line + x * (scene->bpp / 8));
	*((unsigned int*)dst) = color;
}

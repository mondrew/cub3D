/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:01:53 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:12:00 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_line_len(double y1, double x1, t_cub *scene)
{
	float	x2;
	float	y2;
	float	dx;
	float	dy;

	x2 = scene->plr_glb_x;
	y2 = scene->plr_glb_y;
	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

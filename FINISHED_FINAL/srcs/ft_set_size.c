/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:00:43 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:10:41 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_size(t_cub *scene)
{
	scene->size = scene->final_dist;
	scene->size *= cos(scene->ray_angle - scene->plr_angle);
	scene->size = (64 / scene->size) * scene->dist_to_pp;
	scene->scale = scene->size / 64;
}

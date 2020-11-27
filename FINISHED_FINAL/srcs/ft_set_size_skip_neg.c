/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_size_skip_neg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:23:43 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:26:33 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_size_skip_neg(int *j, int *x, double dist, t_cub *scene)
{
	scene->size = dist;
	scene->kj = 0;
	*j = (int)(scene->kj / scene->scale);
	scene->size = (64 / scene->size) * scene->dist_to_pp;
	scene->scale = scene->size / 64;
	*x = *x - scene->size / 2;
	while (*j < 64 && *x < 0 && scene->kj < scene->size && *x < scene->res_x)
	{
		(*x)++;
		scene->kj++;
		*j = (int)(scene->kj / scene->scale);
	}
}

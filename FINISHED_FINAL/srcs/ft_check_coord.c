/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:02:07 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:12:26 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_coord(t_cub *scene)
{
	if (scene->ray_map_x < 0 || scene->ray_map_y < 0 ||
		scene->ray_map_x > scene->map_max_x || \
		scene->ray_map_y > scene->map_max_y)
		return (0);
	return (1);
}

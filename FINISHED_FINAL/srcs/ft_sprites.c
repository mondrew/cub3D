/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 19:31:33 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:29:56 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_sprites(double dist_arr[], t_cub *scene)
{
	t_sprite		sprite[20];
	int				i;

	i = 0;
	ft_set_null_struct(sprite);
	ft_check_set_angle('p', scene);
	while (scene->plane_x < scene->res_x)
	{
		ft_check_set_angle('r', scene);
		ft_set_ray_dir(scene);
		ft_set_delta(scene);
		ft_hor_inter_sprite(&i, sprite, scene);
		ft_ver_inter_sprite(&i, sprite, scene);
		scene->ray_angle -= ((PI / 3) / (double)scene->res_x);
		scene->plane_x++;
	}
	if (i == 0)
		return (0);
	i--;
	ft_sprt(&i, sprite, dist_arr, scene);
	return (0);
}

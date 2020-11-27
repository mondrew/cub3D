/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 00:49:11 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/14 10:45:19 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_raycaster(t_cub *scene)
{
	double	dist_arr[scene->res_x];

	ft_check_set_angle('p', scene);
	while (scene->plane_x < scene->res_x)
	{
		ft_check_set_angle('r', scene);
		ft_set_ray_dir(scene);
		ft_set_delta(scene);
		ft_horizontal_intersections(scene);
		ft_vertical_intersections(scene);
		ft_offset_dist(scene);
		ft_draw_the_line(scene->plane_x, scene);
		dist_arr[scene->plane_x] = scene->final_dist;
		scene->ray_angle -= ((PI / 3) / (double)scene->res_x);
		scene->plane_x++;
	}
	ft_sprites(dist_arr, scene);
	if (scene->save_flag == 1 && !(ft_create_bmp(scene)))
		return (0);
	else if (scene->save_flag != 1)
		mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, \
				scene->img_ptr, 0, 0);
	return (1);
}

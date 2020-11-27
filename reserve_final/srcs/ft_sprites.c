/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 19:31:33 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 10:16:56 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_unique(t_sprite sprite[], t_cub *scene)
{
	int i;

	i = 0;
	while (i < 20)
	{
		if ((sprite[i]).x == (scene->ray_map_x * 64 + 32))
			return (0);
		if ((sprite[i]).y == (scene->ray_map_y * 64 + 32))
			return (0);
		i++;
	}
	return (1);
}

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

void	ft_paint_sprite(int x, int y, t_cub *scene)
{
	if (scene->save_flag == 1 && scene->color != 0x00000000)
		scene->array[y][x] = scene->color;
	else if (scene->color != 0x00000000)
		ft_my_pixel_put(scene, x, y, scene->color);
}

void	ft_draw_sprite(int x, double dist, t_cub *scene, double dist_arr[])
{
	int		i;
	int		j;
	int		y;

	ft_set_size_skip_neg(&j, &x, dist, scene);
	while (j < 64 && scene->kj < scene->size && x < scene->res_x)
	{
		y = scene->res_y / 2 - scene->size / 2;
		scene->ki = 0;
		i = (int)(scene->ki / scene->scale);
		while (i < 64 && scene->ki < scene->size && y < scene->res_y)
		{
			scene->color = *((unsigned int *)(scene->addr_sprite + \
				(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
			if (dist < dist_arr[x])
				ft_paint_sprite(x, y, scene);
			y++;
			scene->ki++;
			i = (int)(scene->ki / scene->scale);
		}
		x++;
		scene->kj++;
		j = (int)(scene->kj / scene->scale);
	}
}

void	ft_add_sprite_data(int *i, t_sprite spt[], t_cub *scene)
{
	if (ft_check_coord(scene) != 0 && ft_check_wall_sprite(scene) == 2 && \
			ft_unique(spt, scene) != 0)
	{
		(spt[*i]).x = scene->ray_map_x * 64 + 32;
		(spt[*i]).y = scene->ray_map_y * 64 + 32;
		if ((spt[*i]).x < scene->plr_glb_x)
			scene->mx = -1;
		if ((spt[*i]).y < scene->plr_glb_y)
			scene->my = -1;
		if (((spt[*i]).angle = atan2(scene->my * ((spt[*i]).y - \
		scene->plr_glb_y), scene->mx * ((spt[*i]).x - scene->plr_glb_x))) < 0)
			spt[*i].angle *= -1;
		if ((spt[*i]).x >= scene->plr_glb_x && (spt[*i]).y <= scene->plr_glb_y)
			(spt[*i]).abs_angle = (spt[*i]).angle;
		if ((spt[*i]).x < scene->plr_glb_x && (spt[*i]).y <= scene->plr_glb_y)
			(spt[*i]).abs_angle = PI - (spt[*i]).angle;
		if ((spt[*i]).x <= scene->plr_glb_x && (spt[*i]).y > scene->plr_glb_y)
			(spt[*i]).abs_angle = PI + (spt[*i]).angle;
		if ((spt[*i]).x > scene->plr_glb_x && (spt[*i]).y > scene->plr_glb_y)
			(spt[*i]).abs_angle = 2 * PI - (spt[*i]).angle;
		(spt[*i]).dist = sqrt(pow(scene->plr_glb_x - (spt[*i]).x, 2) + \
			pow(scene->plr_glb_y - (spt[*i]).y, 2));
		(*i)++;
	}
}

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

void	ft_ver_inter_sprite(int *i, t_sprite sprite[], t_cub *scene)
{
	if (scene->dir_x != 0)
	{
		if (scene->dir_x > 0)
			scene->vi_x = ((int)(scene->plr_glb_x / 64)) * 64 + 64;
		if (scene->dir_x < 0)
			scene->vi_x = ((int)(scene->plr_glb_x / 64)) * 64 - 0.0001;
		scene->ray_map_x = scene->vi_x / 64;
		scene->vi_y = scene->plr_glb_y + \
			(scene->plr_glb_x - scene->vi_x) * (tan(scene->ray_angle));
		scene->ray_map_y = scene->vi_y / 64;
		while (ft_check_coord(scene) != 0 && ft_check_wall_sprite(scene) != 1)
		{
			ft_add_sprite_data(i, sprite, scene);
			scene->vi_x = scene->vi_x + scene->vi_dx;
			scene->vi_y = scene->vi_y + scene->vi_dy;
			scene->ray_map_x = scene->vi_x / 64;
			scene->ray_map_y = scene->vi_y / 64;
		}
	}
}

void	ft_sprt(int *in, t_sprite sprite[], double dist_arr[], t_cub *scene)
{
	double	start_angle;
	int		x_sprite;
	int		i;

	i = *in;
	while (i >= 0)
	{
		start_angle = scene->plr_angle - (PI / 6);
		if (start_angle < 0)
			start_angle += 2 * PI;
		if (start_angle > 2 * PI)
			start_angle -= 2 * PI;
		if (sprite[i].abs_angle > 0 && sprite[i].abs_angle < PI / 2 \
				&& start_angle > 3 * PI / 2 && start_angle < 2 * PI)
			sprite[i].abs_angle += 2 * PI;
		if (sprite[i].abs_angle < 2 * PI && sprite[i].abs_angle > 3 * PI / 2 \
				&& start_angle > 0 && start_angle < PI / 2)
			sprite[i].abs_angle -= 2 * PI;
		x_sprite = (double)scene->res_x - ((sprite[i]).abs_angle - \
			start_angle) / (PI / 3) * (double)scene->res_x;
		ft_draw_sprite(x_sprite, (sprite[i]).dist, scene, dist_arr);
		i--;
	}
	*in = i;
}

int		ft_sprites(double dist_arr[], t_cub *scene)
{
	t_sprite		sprite[20];
	int				i;

	i = 0;
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

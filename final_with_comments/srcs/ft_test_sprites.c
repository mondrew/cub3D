/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:40:30 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/03 18:39:57 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int		ft_draw_sprite(int x, double line_len, t_cub *scene)
{
	int		y;
	int		ny;
	double	real_height;
	int		screen_h;
	int		color;
	int		i;
	int		counter;
	int		grid_size;
	int		j;
   
	ny = 0;
	i = 0;
	j = scene->offset;
	grid_size = 64;
	real_height = (64 / line_len) * scene->dist_to_pp;
	if (real_height > scene->res_y)
		screen_h = scene->res_y;
	else
		screen_h = ceil(real_height); // ROUNDED UP + 1??
	y = scene->res_y / 2 - screen_h / 2;
	// Sky-------------------
	while (ny < y)
	{
		if (scene->save_flag == 1)
			scene->array[ny][x] = scene->ceiling_color;
		else
			ft_my_pixel_put(scene, x, ny, scene->ceiling_color); // sky
		ny++;
	}
	// SPRITE -------------------------
	while (screen_h > 0)
	{
		color = *((unsigned int *)(scene->addr_sprite + \
				(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
		counter = screen_h / grid_size;
		screen_h -= counter;
		while (counter > 0)
		{
			if (scene->save_flag == 1 && color != 0x00000000)
				scene->array[y][x] = color;
			else if (color != 0x00000000)
				ft_my_pixel_put(scene, x, y, color);
			y++;
			counter--;
		}
		grid_size--;
		i++;
	}
	// Floor ----------------------------
	while (y < scene->res_y)
	{
		if (scene->save_flag == 1)
			scene->array[y][x] = scene->floor_color;
		else
			ft_my_pixel_put(scene, x, y, scene->floor_color); // ground
		y++;
	}
	return (0);
}

void		ft_test_sprites(t_cub *scene)
{
	//-===============//Finding horizontal intersections//==================-//
	// Находим координату Y первого пересечения с горизонтальной осью
	if (scene->dir_y != 0)
	{
		if (scene->dir_y < 0)
			scene->s_hi_y = ((int)(scene->plr_glb_y / 64)) * 64 - 0.0001;
		if (scene->dir_y > 0) // поменял знак тут и выше
			scene->s_hi_y = ((int)(scene->plr_glb_y / 64)) * 64 + 64;
		// Находим координату Y на карте (ячейку)
		scene->s_ray_map_y = scene->s_hi_y / 64;

		// Находим координату X первого пересечения с горизонтальной осью
		scene->s_hi_x = scene->plr_glb_x + \
			(scene->plr_glb_y - scene->s_hi_y) / tan(scene->ray_angle);
		// Находим координату X на карте (ячейку)
		scene->s_ray_map_x = scene->s_hi_x / 64;

		// Проверяем, есть ли в данной ячейке спрайт
		while (ft_sprite_coord(scene) != 0 && !(ft_check_is_sprite_wall(scene)))
		{
			// Next possible point
			scene->s_hi_x = scene->s_hi_x + scene->hi_dx;
			scene->s_hi_y = scene->s_hi_y + scene->hi_dy;
			// Находим координаты на карте и проверяем, есть ли там стена
			scene->s_ray_map_x = scene->s_hi_x / 64;
			scene->s_ray_map_y = scene->s_hi_y / 64;
			if (ft_check_is_sprite_wall(scene) == 2)
			{
				//Calculating distance
				scene->sprite_len_h = abs(scene->s_hi_y - scene->plr_glb_y);
				//Calculating offset for the texture
				if (scene->dir_y > 0)
					scene->offset = (int)scene->s_hi_x % 64;
				else
					scene->offset = 63 - (int)scene->s_hi_x % 64;
				ft_draw_sprite(scene->plane_x, scene->sprite_len_h, scene);//////////
			}
		}
	}

	// Находим координату X первого пересечения с вертикальной осью
	if (scene->dir_x != 0)
	{
		if (scene->dir_x > 0)
			scene->s_vi_x = ((int)(scene->plr_glb_x / 64)) * 64 + 64;
		if (scene->dir_x < 0)
			scene->s_vi_x = ((int)(scene->plr_glb_x / 64)) * 64 - 0.0001;

		// Находим координату X на карте (ячейку)
		scene->s_ray_map_x = scene->s_vi_x / 64;

		// Находим координату Y первого пересечения с вертикальной осью
		scene->s_vi_y = scene->plr_glb_y + \
			(scene->plr_glb_x - scene->s_vi_x) * (tan(scene->ray_angle)); // added abs
		// Находим координату Y на карте (ячейку)
		scene->s_ray_map_y = scene->s_vi_y / 64;

		// Проверяем, есть ли в данной ячейке стена или спрайт
		while (ft_check_coord(scene) != 0 && !(ft_check_is_sprite_wall(scene)))
		{
			// Next possible point
			scene->s_vi_x = scene->s_vi_x + scene->vi_dx;
			scene->s_vi_y = scene->s_vi_y + scene->vi_dy;
			// Находим координаты на карте и проверяем, есть ли там стена
			scene->s_ray_map_x = scene->s_vi_x / 64;
			scene->s_ray_map_y = scene->s_vi_y / 64;
			if (ft_check_is_sprite_wall(scene) == 2)
			{
				//Calculating distance
				scene->sprite_len_v = abs(scene->s_vi_x - scene->plr_glb_x);
				//Calculating offset for the texture
				if (scene->dir_x > 0)
					scene->offset = (int)scene->s_vi_y % 64;
				else
					scene->offset = 63 - (int)scene->s_vi_y % 64;
				ft_draw_sprite(scene->plane_x, scene->sprite_len_v, scene);//////////
			}
		}
	}
}

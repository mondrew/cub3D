/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 19:31:33 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/08 15:28:57 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#define PI 3.14159265359

int			ft_check_coord(t_cub *scene);
int			ft_check_is_wall_sprite(t_cub *scene);

int		ft_unique(t_sprite sprite[], t_cub *scene)
{
	int i;

	i = 0;
	while (i < 10)
	{
		if ((sprite[i]).x == (scene->ray_map_x * 64 + 32))
			return (0);
		if ((sprite[i]).y == (scene->ray_map_y * 64 + 32))
			return (0);
		i++;
	}
	return (1);
}

int			ft_add_sprites(t_cub *scene) // deleted double *array[]
{
	t_sprite		sprite[20];
	int				i;
	unsigned int	color;

	i = 0;

	if (scene->plr_angle < 0)
		scene->plr_angle += 2 * PI;
	else if (scene->plr_angle > 2 * PI)
		scene->plr_angle -= 2 * PI;
	// Задаем угол первого луча
	scene->ray_angle = scene->plr_angle + scene->fov_angle / 2;
	scene->plane_x = 0; // Обнуляем индекс
	while (scene->plane_x < scene->res_x)
	{
		// Проверка угла луча на меньше 0 или больше 360
		if (scene->ray_angle < 0)
			scene->ray_angle += 2 * PI;
		else if (scene->ray_angle > 2 * PI)
			scene->ray_angle -= 2 * PI;

		// Угол наклона луча - находим знак dir_x
		if (scene->ray_angle == PI / 2 || scene->ray_angle == 3 * PI / 2)
			scene->dir_x = 0;
		else if (scene->ray_angle > 3 * PI / 2 && scene->ray_angle <= 2 * PI || \
				scene->ray_angle >= 0 && scene->ray_angle < PI / 2)
			scene->dir_x = 1;
		else if (scene->ray_angle > PI / 2 && scene->ray_angle <= PI || \
				scene->ray_angle > PI && scene->ray_angle < 3 * PI / 2)
			scene->dir_x = -1;

		// Угол наклона луча - находим знак dir_y
		if (scene->ray_angle == 0 || scene->ray_angle == PI || \
				scene->ray_angle == 2 * PI)
			scene->dir_y = 0;
		else if (scene->ray_angle > 0 && scene->ray_angle < PI)
			scene->dir_y = -1; // поменял знак тут и ниже
		else if (scene->ray_angle > PI && scene->ray_angle < 2 * PI)
			scene->dir_y = 1;

		// Находим dy - расстояние между первым и последующими гор.пересеч-ми
		scene->hi_dy = 64 * scene->dir_y;
		// Находим dx
		if (tan(scene->ray_angle) < 0) // СОМНЕНИЯ !!!!!!!
			scene->hi_dx = (-1) * scene->dir_x * 64 / tan(scene->ray_angle); // added abs
		else
			scene->hi_dx = scene->dir_x * 64 / tan(scene->ray_angle);

		//-===============//Finding horizontal intersections//==================-//
		// Находим координату Y первого пересечения с горизонтальной осью
		if (scene->dir_y != 0)
		{
			if (scene->dir_y < 0)
				scene->hi_y = ((int)(scene->plr_glb_y / 64)) * 64 - 0.0001;
			if (scene->dir_y > 0) // поменял знак тут и выше
				scene->hi_y = ((int)(scene->plr_glb_y / 64)) * 64 + 64;
			// Находим координату Y на карте (ячейку)
			scene->ray_map_y = scene->hi_y / 64;

			// Находим координату X первого пересечения с горизонтальной осью
			scene->hi_x = scene->plr_glb_x + \
				(scene->plr_glb_y - scene->hi_y) / tan(scene->ray_angle);
			// Находим координату X на карте (ячейку)
			scene->ray_map_x = scene->hi_x / 64;

			// Проверяем, есть ли в данной ячейке спрайт
			while (ft_check_coord(scene) != 0 && ft_check_is_wall_sprite(scene) != 1)
			{
				// Next possible point
				scene->hi_x = scene->hi_x + scene->hi_dx;
				scene->hi_y = scene->hi_y + scene->hi_dy;
				// Находим координаты на карте и проверяем, есть ли там стена
				scene->ray_map_x = scene->hi_x / 64;
				scene->ray_map_y = scene->hi_y / 64;
				if (ft_check_is_wall_sprite(scene) == 2 && ft_unique(sprite, scene) != 0)
				{
					printf("-----test---\n");
					(sprite[i]).x = scene->ray_map_x * 64 + 32;
					(sprite[i]).y = scene->ray_map_y * 64 + 32;
					(sprite[i]).angle = atan2((sprite[i]).y - scene->plr_glb_y, \
							(sprite[i]).x - scene->plr_glb_x);
					while ((sprite[i]).angle - scene->plr_angle < -PI)
						(sprite[i]).angle += 2 * PI;
					while ((sprite[i]).angle - scene->plr_angle > PI)
						(sprite[i]).angle -= 2 * PI;
					(sprite[i]).dist = sqrt(pow(scene->plr_glb_x - (sprite[i]).x, 2) + \
									   pow(scene->plr_glb_y - (sprite[i]).y, 2));
					if ((int)(scene->res_y / (sprite[i]).dist) < 1000)
						(sprite[i]).size = (int)(scene->res_y / (sprite[i]).dist);
					else
						(sprite[i]).size = 1000;
					//(sprite[i]).size = min(1000, (int)(scene->res_y / (sprite[i]).dist));
					i++;
				}
			}
		}

		//-===============//Finding vertical intersections//==================-//
		
		// Находим dx - расстояние между первым и последующими верт.пересеч-ми
		scene->vi_dx = 64 * scene->dir_x;
		// Находим dy
		if (tan(scene->ray_angle) < 0) // СОМНЕНИЯ!!!!!!!
			scene->vi_dy = (-1) * scene->dir_y * 64 * tan(scene->ray_angle); // added abs
		if (tan(scene->ray_angle) > 0)
			scene->vi_dy = scene->dir_y * 64 * tan(scene->ray_angle);

		// Находим координату X первого пересечения с вертикальной осью
		if (scene->dir_x != 0)
		{
			if (scene->dir_x > 0)
				scene->vi_x = ((int)(scene->plr_glb_x / 64)) * 64 + 64;
			if (scene->dir_x < 0)
				scene->vi_x = ((int)(scene->plr_glb_x / 64)) * 64 - 0.0001;

			// Находим координату X на карте (ячейку)
			scene->ray_map_x = scene->vi_x / 64;

			// Находим координату Y первого пересечения с вертикальной осью
			scene->vi_y = scene->plr_glb_y + \
				(scene->plr_glb_x - scene->vi_x) * (tan(scene->ray_angle)); // added abs
			// Находим координату Y на карте (ячейку)
			scene->ray_map_y = scene->vi_y / 64;

			// Проверяем, есть ли в данной ячейке стена или спрайт
			while (ft_check_coord(scene) != 0 && ft_check_is_wall_sprite(scene) != 1)
			{
				// Next possible point
				scene->vi_x = scene->vi_x + scene->vi_dx;
				scene->vi_y = scene->vi_y + scene->vi_dy;
				// Находим координаты на карте и проверяем, есть ли там стена
				scene->ray_map_x = scene->vi_x / 64;
				scene->ray_map_y = scene->vi_y / 64;
				if (ft_check_is_wall_sprite(scene) == 2 && ft_unique(sprite, scene) != 0)
				{
					printf("-----test---\n");
					(sprite[i]).x = scene->ray_map_x * 64 + 32;
					(sprite[i]).y = scene->ray_map_y * 64 + 32;
					(sprite[i]).angle = atan2((sprite[i]).y - scene->plr_glb_y, \
							(sprite[i]).x - scene->plr_glb_x);
					while ((sprite[i]).angle - scene->plr_angle < -PI)
						(sprite[i]).angle += 2 * PI;
					while ((sprite[i]).angle - scene->plr_angle > PI)
						(sprite[i]).angle -= 2 * PI;
					(sprite[i]).dist = sqrt(pow(scene->plr_glb_x - (sprite[i]).x, 2) + \
									   pow(scene->plr_glb_y - (sprite[i]).y, 2));
					if ((int)(scene->res_y / (sprite[i]).dist) < 1000)
						(sprite[i]).size = (int)(scene->res_y / (sprite[i]).dist);
					else
						(sprite[i]).size = 1000;
					//(sprite[i]).size = min(1000, (int)(scene->res_y / (sprite[i]).dist));
					i++;
				}
			}
		}
		scene->ray_angle -= scene->angle_inc;
		scene->plane_x++;
	}
	if (i == 0) // If there are no sprites
		return (0);
	int a = 0;
	while (a < 10)
	{
		printf("Coord a_x: %f\n", (sprite[i]).x);
		printf("Coord a_y: %f\n", (sprite[i]).y);
		a++;
	}
	unsigned int x;
	unsigned int y;
	x = 0;
	y = 0;
	while (i >= 0)
	{
		// Top left sprite angle coordinates
		scene->s_offset_x = ((sprite[i]).angle - scene->plr_angle) * \
			scene->res_x / 60 + scene->res_x / 2 - (sprite[i]).size / 2;
		scene->s_offset_y = scene->res_y / 2 - (sprite[i]).size / 2;
		while (y < (sprite[i]).size)
		{
			if (scene->s_offset_y + y >= 0 && scene->s_offset_y + y < scene->res_y)
			{
				x = 0;
				while (x < (sprite[i]).size)
				{
					if (scene->s_offset_x + x >= 0 && scene->s_offset_x + x < scene->res_x)
					{
						color = *((unsigned int *)(scene->addr_sprite + \
							(y * scene->size_line_tex + x * (scene->bpp_tex / 8))));
						if (scene->save_flag == 1)
							scene->array[scene->s_offset_y + y][scene->s_offset_x + x] = color;
						else
							ft_my_pixel_put(scene, scene->s_offset_x + x, scene->s_offset_y + y, color);
					}
					x++;
				}
			}
			y++;
		}
		i--;
	}
}

/*int		ft_draw_sprite(int x, double line_len, t_cub *scene)
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
*/

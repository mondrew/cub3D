/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 19:31:33 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/07 16:12:13 by mondrew          ###   ########.fr       */
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

int		ft_draw_sprite(int x, double dist, t_cub *scene, double dist_arr[])
{
	int		i; // строка в текстуре
	int		j; // столбец в текстуре
	int		y;
	double 	real_height;
	int		screen_h;
	int		screen_w;
	int		counter_x;
	int		counter_y;
	int		grid_size_x;
	int		grid_size_y;
	int		hold_size;
	int		color;

	i = 0;
	j = 0;
	grid_size_x = 64;
	grid_size_y = 64;
	real_height = (64 / dist) * scene->dist_to_pp;
	if (real_height > scene->res_y)
		screen_h = scene->res_y;
	else
		screen_h = real_height;
	hold_size = screen_h;
	screen_w = screen_h;
	x = x - screen_w / 2; // x start
	while (x < 0 && screen_w > 0)
	{
		counter_x = round((float)screen_w / (float)grid_size_x);
		screen_w -= counter_x;
		while (counter_x > 0)
		{
			x++;
			counter_x--;
		}
		grid_size_x--;
		j++;
		while (x > 0)
		{
			x--;
			screen_w++;
		}
	}

	while (screen_w > 0 && x <= scene->res_x && dist < dist_arr[x])
	{
		counter_x = round((float)screen_w / (float)grid_size_x);
		screen_w -= counter_x;
		while (counter_x > 0)
		{
			screen_h = hold_size;
			i = 0;
			y = scene->res_y / 2 - screen_h / 2;
			grid_size_y = 64;
			while (screen_h > 0)
			{
				color = *((unsigned int *)(scene->addr_sprite + (i * scene->size_line_tex + \
							j * (scene->bpp_tex / 8))));
				counter_y = round((float)screen_h / (float)grid_size_y);
				screen_h -= counter_y;
				while (counter_y > 0)
				{
					if (scene->save_flag == 1 && color != 0x00000000)
						scene->array[y][x] = color;
					else if (color != 0x00000000)
						ft_my_pixel_put(scene, x, y, color);
					y++;
					counter_y--;
				}
				grid_size_y--;
				i++;
			}
			x++;
			counter_x--;
		}
		grid_size_x--;
		j++;
	}
	return (0);
}

int			ft_sprites(double dist_arr[], t_cub *scene)
{
	t_sprite		sprite[20];
	int				i;
	unsigned int	color;
	double mx = 1;
	double my = 1;

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
				if (ft_check_coord(scene) != 0 && ft_check_is_wall_sprite(scene) == 2 && \
						ft_unique(sprite, scene) != 0)
				{
					(sprite[i]).x = scene->ray_map_x * 64 + 32;
					(sprite[i]).y = scene->ray_map_y * 64 + 32;
					if ((sprite[i]).x < scene->plr_glb_x)
						mx = -1;
					if ((sprite[i]).y < scene->plr_glb_y)
						my = -1;
					(sprite[i]).angle = atan2(my * ((sprite[i]).y - scene->plr_glb_y), \
							mx * ((sprite[i]).x - scene->plr_glb_x));

					if ((sprite[i]).x >= scene->plr_glb_x && (sprite[i]).y <= scene->plr_glb_y)
						(sprite[i]).abs_angle = (sprite[i]).angle;
					if ((sprite[i]).x < scene->plr_glb_x && (sprite[i]).y <= scene->plr_glb_y)
						(sprite[i]).abs_angle = PI - (sprite[i]).angle;
					if ((sprite[i]).x <= scene->plr_glb_x && (sprite[i]).y > scene->plr_glb_y)
						(sprite[i]).abs_angle = PI + (sprite[i]).angle;
					if ((sprite[i]).x > scene->plr_glb_x && (sprite[i]).y > scene->plr_glb_y)
						(sprite[i]).abs_angle = 2 * PI - (sprite[i]).angle;

					(sprite[i]).dist = sqrt(pow(scene->plr_glb_x - (sprite[i]).x, 2) + \
									   pow(scene->plr_glb_y - (sprite[i]).y, 2));

					i++;
				}
				// Next possible point
				scene->hi_x = scene->hi_x + scene->hi_dx;
				scene->hi_y = scene->hi_y + scene->hi_dy;
				// Находим координаты на карте и проверяем, есть ли там стена
				scene->ray_map_x = scene->hi_x / 64;
				scene->ray_map_y = scene->hi_y / 64;
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
				if (ft_check_coord(scene) != 0 && ft_check_is_wall_sprite(scene) == 2 && \
						ft_unique(sprite, scene) != 0)
				{
					(sprite[i]).x = scene->ray_map_x * 64 + 32;
					(sprite[i]).y = scene->ray_map_y * 64 + 32;
					if ((sprite[i]).x < scene->plr_glb_x)
						mx = -1;
					if ((sprite[i]).y < scene->plr_glb_y)
						my = -1;
					(sprite[i]).angle = atan2(my * ((sprite[i]).y - scene->plr_glb_y), \
							mx * ((sprite[i]).x - scene->plr_glb_x));

					if ((sprite[i]).x >= scene->plr_glb_x && (sprite[i]).y <= scene->plr_glb_y)
						(sprite[i]).abs_angle = (sprite[i]).angle;
					if ((sprite[i]).x < scene->plr_glb_x && (sprite[i]).y <= scene->plr_glb_y)
						(sprite[i]).abs_angle = PI - (sprite[i]).angle;
					if ((sprite[i]).x <= scene->plr_glb_x && (sprite[i]).y > scene->plr_glb_y)
						(sprite[i]).abs_angle = PI + (sprite[i]).angle;
					if ((sprite[i]).x > scene->plr_glb_x && (sprite[i]).y > scene->plr_glb_y)
						(sprite[i]).abs_angle = 2 * PI - (sprite[i]).angle;

					(sprite[i]).dist = sqrt(pow(scene->plr_glb_x - (sprite[i]).x, 2) + \
									   pow(scene->plr_glb_y - (sprite[i]).y, 2));
					i++;
				}
				// Next possible point
				scene->vi_x = scene->vi_x + scene->vi_dx;
				scene->vi_y = scene->vi_y + scene->vi_dy;
				// Находим координаты на карте и проверяем, есть ли там стена
				scene->ray_map_x = scene->vi_x / 64;
				scene->ray_map_y = scene->vi_y / 64;
			}
		}
		scene->ray_angle -= scene->angle_inc;
		scene->plane_x++;
	}
	printf("i: %d\n", i);
	if (i == 0) // If there are no sprites
		return (0);
	i--;
	printf("i: %d\n", i);
		double	start_angle;
		int		x_sprite;
	while (i >= 0)
	{
		start_angle = scene->plr_angle - scene->fov_angle / 2;
		printf("-1---start_angle: %f\n", start_angle);
		if (start_angle < 0)
			start_angle += 2 * PI;
		if (start_angle > 2 * PI)
			start_angle -= 2 * PI;
		printf("-2---start_angle: %f\n", start_angle);
		if (sprite[i].abs_angle > 0 && sprite[i].abs_angle < PI / 2 \
				&& start_angle > 3 * PI / 2 && start_angle < 2 * PI)
			sprite[i].abs_angle += 2 * PI;
		if (sprite[i].abs_angle < 2 * PI && sprite[i].abs_angle > 3 * PI / 2 \
				&& start_angle > 0 && start_angle < PI / 2)
			sprite[i].abs_angle -= 2 * PI;
		printf("res_x: %d\n", scene->res_x);
		x_sprite = (double)scene->res_x - ((sprite[i]).abs_angle - start_angle) /
			scene->fov_angle * (double)scene->res_x;
		printf("dist to pp: %f\n", scene->dist_to_pp);
		printf("plr_angle: %f\n", 180 / PI *scene->plr_angle);
		printf("fov: %f\n", 180 / PI * scene->fov_angle);
		printf("sprite angle: %f\n", 180 / PI * (sprite[i]).angle);
		printf("start_angle: %f\n", 180 / PI * start_angle);
		printf("sprite_abs_angle: %f\n", 180 / PI * (sprite[i]).abs_angle);
		printf("x_sprite: %d\n", x_sprite);

		ft_draw_sprite(x_sprite, (sprite[i]).dist, scene, dist_arr);
		i--;
	}
	return (0);
}

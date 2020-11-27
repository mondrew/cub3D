/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 00:49:11 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/03 09:18:21 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mlx.h"
#include "mlx_int.h"
#include "cub3d.h"
#define ESC 65307
#define W 119
#define A 97
#define S 115
#define D 100
#define ARROW_LEFT 65361
#define ARROW_RIGHT 65363
#define PI 3.14159265359

int		ft_draw_the_line(int x, double line_len, t_cub *scene)
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
   
	//printf("----------TEST_draw_line-------------------------\n");
	//printf("offset---: %d\n", j);
	//printf("dir_x---: %d\n", scene->dir_x);
	//printf("dir_y---: %d\n", scene->dir_y);
	ny = 0;
	i = 0;
	j = scene->offset;
	grid_size = 64;
	line_len *= cos(scene->ray_angle - scene->plr_angle); // fixing fisheye effect
	real_height = (64 / line_len) * scene->dist_to_pp;
	//printf("real_height: %f\n", real_height);
	if (real_height > scene->res_y)
		screen_h = scene->res_y;
	else
		screen_h = ceil(real_height); // ROUNDED UP + 1??
	//printf("screen_h: %d\n", screen_h);
	y = scene->res_y / 2 - screen_h / 2;
	// Sky-------------------
	while (ny < y)
	{
		if (scene->save_flag == 1)
			scene->array[ny][x] = 0x00483d8b;
		else
			ft_my_pixel_put(scene, x, ny, 0x00483d8b); // sky
		ny++;
	}
	// Wall ---------------------------
	if (scene->line_len_h < scene->line_len_v) // горизонтальная стена
	{
		//printf("--------LINE_LEN_H\n");
		if (scene->dir_y >= 0)
		{
			while (screen_h > 0)
			{
				color = *((unsigned int *)(scene->addr_no_tex + \
						(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
				counter = screen_h / grid_size;
				screen_h -= counter;
				//printf("color---: %d\n", color);
				//printf("counter---: %d\n", counter);
				while (counter > 0)
				{
					if (scene->save_flag == 1)
						scene->array[y][x] = color;
					else
						ft_my_pixel_put(scene, x, y, color);
					y++;
					counter--;
				}
				grid_size--;
				i++;
			}
		}
		if (scene->dir_y < 0)
		{
			while (screen_h > 0)
			{
				color = *((unsigned int *)(scene->addr_so_tex + \
						(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
				counter = screen_h / grid_size;
				screen_h -= counter;
				while (counter > 0)
				{
					if (scene->save_flag == 1)
						scene->array[y][x] = color;
					else
						ft_my_pixel_put(scene, x, y, color);
					y++;
					counter--;
				}
				grid_size--;
				i++;
			}
		}
	}
	if (scene->line_len_h > scene->line_len_v) // вертикальная стена
	{
		//printf("--------LINE_LEN_V\n");
		//printf("---test---\n");
		if (scene->dir_x >= 0)
		{
			while (screen_h > 0)
			{
				color = *((unsigned int *)(scene->addr_ea_tex + \
						(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
				counter = screen_h / grid_size;
				screen_h -= counter;
				while (counter > 0)
				{
					if (scene->save_flag == 1)
						scene->array[y][x] = color;
					else
						ft_my_pixel_put(scene, x, y, color);
					y++;
					counter--;
				}
				grid_size--;
				i++;
			}
		}
		if (scene->dir_x < 0)
		{
			while (screen_h > 0)
			{
				color = *((unsigned int *)(scene->addr_we_tex + \
						(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
				counter = screen_h / grid_size;
				screen_h -= counter;
				//printf("color---: %d\n", color);
				//printf("counter---: %d\n", counter);
				while (counter > 0)
				{
					if (scene->save_flag == 1)
						scene->array[y][x] = color;
					else
						ft_my_pixel_put(scene, x, y, color);
					y++;
					counter--;
				}
				grid_size--;
				i++;
			}
		}
	}
	// Floor ----------------------------
	while (y < scene->res_y)
	{
		if (scene->save_flag == 1)
			scene->array[y][x] = 0x002f4f4f;
		else
			ft_my_pixel_put(scene, x, y, 0x002f4f4f); // ground
		y++;
	}
	return (0);
}

int		ft_check_is_wall_sprite(t_cub *scene)
{
	if (scene->map[scene->ray_map_y][scene->ray_map_x] == '1')
		return (1);
	else if (scene->map[scene->ray_map_y][scene->ray_map_x] == '2')
		return (2);
	return (0);
}

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

int		ft_check_coord(t_cub *scene)
{
	if (scene->ray_map_x < 0 || scene->ray_map_y < 0 ||
		scene->ray_map_x > scene->map_max_x || scene->ray_map_y > scene->map_max_y)
		return (0);
	return (1);
}

int		ft_raycaster(t_cub *scene)
{
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

			// Проверяем, есть ли в данной ячейке стена или спрайт
			while (ft_check_coord(scene) != 0 && !(ft_check_is_wall_sprite(scene)))
			{
				// Next possible point
				scene->hi_x = scene->hi_x + scene->hi_dx;
				scene->hi_y = scene->hi_y + scene->hi_dy;
				// Находим координаты на карте и проверяем, есть ли там стена
				scene->ray_map_x = scene->hi_x / 64;
				scene->ray_map_y = scene->hi_y / 64;
			}
			scene->line_len_h = ft_line_len(scene->hi_y, scene->hi_x, scene);

//	printf("--||--hi_x: %f\n--||--hi_y: %f\n", scene->hi_x, scene->hi_y);
//	printf("--||--ray_map_x: %d\n--||--ray_map_y: %d\n", scene->ray_map_x, scene->ray_map_y);
//	printf("--||--dir_x: %d || dir_y: %d\n", scene->dir_x, scene->dir_y);
//	printf("--||--line_len_h: %f\n\n", scene->line_len_h);
//	sleep(2);
		}
		else
			scene->line_len_h = 0;

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
			while (ft_check_coord(scene) != 0 && !(ft_check_is_wall_sprite(scene)))
			{
				// Next possible point
				scene->vi_x = scene->vi_x + scene->vi_dx;
				scene->vi_y = scene->vi_y + scene->vi_dy;
				// Находим координаты на карте и проверяем, есть ли там стена
				scene->ray_map_x = scene->vi_x / 64;
				scene->ray_map_y = scene->vi_y / 64;
			}
			scene->line_len_v = ft_line_len(scene->vi_y, scene->vi_x, scene);

	//printf("--||--vi_x: %f\n--||--vi_y: %f\n", scene->vi_x, scene->vi_y);
	//printf("--||--ray_map_x: %d\n--||--ray_map_y: %d\n", scene->ray_map_x, scene->ray_map_y);
	//printf("--||--line_len_v: %f\n\n", scene->line_len_v);
	//sleep(2);

		}
		else
			scene->line_len_v = 0;

		//Calculating offset for the texture
		if (scene->line_len_h < scene->line_len_v)
		{
			if (scene->dir_x > 0)
				scene->offset = (int)scene->hi_x % 64;
			else
				scene->offset = 63 - (int)scene->hi_x % 64;
		}
		else if (scene->line_len_h > scene->line_len_v)
		{
			if (scene->dir_y > 0)
				scene->offset = (int)scene->vi_y % 64;
			else
				scene->offset = 63 - (int)scene->vi_y % 64;
		}
		
		// Checking what intersection is closer: with horisontal or vertical line?
		if (scene->line_len_h < scene->line_len_v)
		{
			if (scene->line_len_h != 0)
				ft_draw_the_line(scene->plane_x, scene->line_len_h, scene);
			else
				ft_draw_the_line(scene->plane_x, scene->line_len_v, scene);
		}
		else if (scene->line_len_h > scene->line_len_v)
		{
			if (scene->line_len_v != 0)
				ft_draw_the_line(scene->plane_x, scene->line_len_v, scene);
			else
				ft_draw_the_line(scene->plane_x, scene->line_len_h, scene);
		}
		static int a = 0;
		printf("----%d\n", a++);
		scene->ray_angle -= scene->angle_inc;
		scene->plane_x++;
	}
	//printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	//printf("player_x: %f\n", scene->plr_glb_x);
	//printf("player_y: %f\n", scene->plr_glb_y);
	//printf("player_angle: %f\n", 57.3 * scene->plr_angle);
	//printf("ray_angle: %f\n", 57.3 * scene->ray_angle);
	//printf("*player_angle: %f\n", scene->plr_angle);
	//printf("*ray_angle: %f\n", scene->ray_angle);
	//printf("tan: %f\n", tan(scene->ray_angle));
	//printf("----dir_x: %d\n", scene->dir_x);
	//printf("----dir_y: %d\n", scene->dir_y);
	//if (scene->line_len_h < scene->line_len_v)
	//{
	//	printf("-line_len_h: %f\n", scene->line_len_h);
	//	printf("line_len_v: %f\n", scene->line_len_v);
	//}
	//else
	//{
	//	printf("-line_len_v: %f\n", scene->line_len_v);
	//	printf("line_len_h: %f\n", scene->line_len_h);
	//}
	if (scene->save_flag == 1)
		ft_create_bmp(scene->res_x, scene->res_y, scene->array);
	else
		mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img_ptr, 0, 0);
	//mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->xpm_no_tex, 0, 0);
	return (0);
}

int		ft_read_keys(int keycode, t_cub *scene)
{
	int x;
	int y;

	if (keycode == ESC)
	{
		printf("EXIT\n");
		exit(0);
	}
	mlx_destroy_image(scene->mlx_ptr, scene->img_ptr);
	scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->res_x, scene->res_y);
	scene->addr = mlx_get_data_addr(scene->img_ptr, &(scene->bpp), \
			&(scene->size_line), &(scene->endian));
	if (keycode == W)
	{
		//y = (scene->plr_glb_x + 10 * cos(scene->plr_angle)) / 64;
		//x = (scene->plr_glb_y
		printf("W\n"); // сначала у потом х
		if ((scene->map[(int)(scene->plr_glb_y - 10 * sin(scene->plr_angle)) / 64][(int)scene->plr_glb_x / 64] != '1') && \
			(scene->map[(int)(scene->plr_glb_y - 10 * sin(scene->plr_angle)) / 64][(int)scene->plr_glb_x / 64] != '2'))
		{
			scene->plr_glb_y -= 10 * sin(scene->plr_angle);
		}
		if ((scene->map[(int)scene->plr_glb_y / 64][(int)(scene->plr_glb_x + 10 * cos(scene->plr_angle)) / 64] != '1') && \
			(scene->map[(int)scene->plr_glb_y / 64][(int)(scene->plr_glb_x + 10 * cos(scene->plr_angle)) / 64] != '2'))
		{
			scene->plr_glb_x += 10 * cos(scene->plr_angle);
		}
	printf("PLAYER_ANGLE: %f\n", scene->plr_angle);
	}
	else if (keycode == S)
	{
		printf("S\n");
		if ((scene->map[(int)(scene->plr_glb_y + 10 * sin(scene->plr_angle)) / 64]\
				[(int)scene->plr_glb_x / 64] != '1') && \
			(scene->map[(int)(scene->plr_glb_y + 10 * sin(scene->plr_angle)) / 64]\
				[(int)scene->plr_glb_x / 64] != '2'))
		{
			scene->plr_glb_y += 10 * sin(scene->plr_angle);
		}
		if ((scene->map[(int)scene->plr_glb_y / 64]\
				[(int)(scene->plr_glb_x - 10 * cos(scene->plr_angle)) / 64] != '1') && \
			(scene->map[(int)scene->plr_glb_y / 64]\
				[(int)(scene->plr_glb_x - 10 * cos(scene->plr_angle)) / 64] != '2'))
		{
			scene->plr_glb_x -= 10 * cos(scene->plr_angle);
		}
	printf("PLAYER_ANGLE: %f\n", scene->plr_angle);
	}
	else if (keycode == A)
	{
		printf("A\n");
		if ((scene->map[(int)(scene->plr_glb_y - 10 * cos(scene->plr_angle)) / 64]\
				[(int)scene->plr_glb_x / 64] != '1') && \
			(scene->map[(int)(scene->plr_glb_y - 10 * cos(scene->plr_angle)) / 64]\
				[(int)scene->plr_glb_x / 64] != '2'))
		{
			scene->plr_glb_y -= 10 * cos(scene->plr_angle);
		}
		if ((scene->map[(int)scene->plr_glb_y / 64]\
				[(int)(scene->plr_glb_x - 10 * sin(scene->plr_angle)) / 64] != '1') && \
			(scene->map[(int)scene->plr_glb_y / 64]\
				[(int)(scene->plr_glb_x - 10 * sin(scene->plr_angle)) / 64] != '2'))
		{
			scene->plr_glb_x -= 10 * sin(scene->plr_angle);
		}
	printf("PLAYER_ANGLE: %f\n", scene->plr_angle);
	}
	else if (keycode == D)
	{
		printf("D\n");
		if ((scene->map[(int)(scene->plr_glb_y + 10 * cos(scene->plr_angle)) / 64]\
				[(int)scene->plr_glb_x / 64] != '1') && \
			(scene->map[(int)(scene->plr_glb_y + 10 * cos(scene->plr_angle)) / 64]\
				[(int)scene->plr_glb_x / 64] != '2'))
		{
			scene->plr_glb_y += 10 * cos(scene->plr_angle);
		}
		if ((scene->map[(int)scene->plr_glb_y / 64]\
				[(int)(scene->plr_glb_x + 10 * sin(scene->plr_angle)) / 64] != '1') && \
			(scene->map[(int)scene->plr_glb_y / 64]\
				[(int)(scene->plr_glb_x + 10 * sin(scene->plr_angle)) / 64] != '2'))
		{
			scene->plr_glb_x += 10 * sin(scene->plr_angle);
		}
	printf("PLAYER_ANGLE: %f\n", scene->plr_angle);
	}
	else if (keycode == ARROW_LEFT)
	{
		printf("<---\n");
		scene->plr_angle += 100 * scene->angle_inc;
	printf("PLAYER_ANGLE: %f\n", scene->plr_angle);
	}
	else if (keycode == ARROW_RIGHT)
	{
		printf("--->\n");
		scene->plr_angle -= 100 * scene->angle_inc;
	printf("PLAYER_ANGLE: %f\n", scene->plr_angle);
	}
	ft_raycaster(scene);
	return (0);
}

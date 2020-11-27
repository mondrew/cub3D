/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 00:49:11 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/12 16:42:30 by mondrew          ###   ########.fr       */
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

int		ft_sprites(double dist_arr[], t_cub *scene);
int		ft_draw_sprite(int x, double line_len, t_cub *scene);
int		ft_create_bmp(int width, int height, unsigned int **pic);

int		ft_get_real_y(double real_height, t_cub *scene)
{
	int y;

	scene->ki = 0;
	y = (int)((double)scene->res_y / 2 - real_height / 2);
	while (y < 0)
	{
		y++;
		scene->ki++;
	}
	return (y);
}

int		ft_draw_the_line(int x, double line_len, t_cub *scene)
{
	int		y;
	int		ny;
	double	real_height;
	int		color;
	int		i;
	int		counter;
	int		grid_size;
	int		j;
	double	scale;
	double	screen_h;

	ny = 0;
	j = scene->offset;
	grid_size = 64;
	line_len *= cos(scene->ray_angle - scene->plr_angle); // fixing fisheye effect
	real_height = (64 / line_len) * scene->dist_to_pp;
	scale = real_height / 64;
	y = ft_get_real_y(real_height, scene);
	i = (int)(scene->ki / scale);
	// Sky-------------------
	while (ny < y)
	{
		if (scene->save_flag == 1)
			scene->array[ny][x] = scene->ceiling_color;
		else
			ft_my_pixel_put(scene, x, ny, scene->ceiling_color); // sky
		ny++;
	}
	// Wall ---------------------------
	if (scene->line_len_h < scene->line_len_v) // горизонтальная стена
	{
		if (scene->dir_y >= 0)
		{
			while (i < 64 && scene->ki < real_height && y < scene->res_y)
			{
				color = *((unsigned int *)(scene->addr_no_tex + \
						(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
				if (scene->save_flag == 1)
					scene->array[y][x] = color;
				else
					ft_my_pixel_put(scene, x, y, color);
				y++;
				scene->ki++;
				i = (int)(scene->ki / scale);
			}
		}
		if (scene->dir_y < 0)
		{
			while (i < 64 && scene->ki < real_height && y < scene->res_y)
			{
				color = *((unsigned int *)(scene->addr_so_tex + \
						(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
				if (scene->save_flag == 1)
					scene->array[y][x] = color;
				else
					ft_my_pixel_put(scene, x, y, color);
					//printf("----debug --y: %d\n", y);
				y++;
				scene->ki++;
				i = (int)(scene->ki / scale);
			}
		}
	}
	if (scene->line_len_h > scene->line_len_v) // вертикальная стена
	{
		if (scene->dir_x >= 0)
		{
			while (i < 64 && scene->ki < real_height && y < scene->res_y)
			{
				color = *((unsigned int *)(scene->addr_ea_tex + \
						(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
				if (scene->save_flag == 1)
					scene->array[y][x] = color;
				else
					ft_my_pixel_put(scene, x, y, color);
					//printf("----debug --y: %d\n", y);
				y++;
				scene->ki++;
				i = (int)(scene->ki / scale);
			}
		}
		if (scene->dir_x < 0)
		{
			while (i < 64 && scene->ki < real_height && y < scene->res_y)
			{
				color = *((unsigned int *)(scene->addr_we_tex + \
						(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
				if (scene->save_flag == 1)
					scene->array[y][x] = color;
				else
					ft_my_pixel_put(scene, x, y, color);
					//printf("----debug --y: %d\n", y);
				y++;
				scene->ki++;
				i = (int)(scene->ki / scale);
			}
		}
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

int		ft_check_is_wall_sprite(t_cub *scene)
{
	if (scene->map[scene->ray_map_y][scene->ray_map_x] == '1')
		return (1);
	else if (scene->map[scene->ray_map_y][scene->ray_map_x] == '2')
		return (2);
	return (0);
}

int		ft_check_is_sprite_wall(t_cub *scene)
{
	if (scene->map[scene->s_ray_map_y][scene->s_ray_map_x] == '1')
		return (1);
	else if (scene->map[scene->s_ray_map_y][scene->s_ray_map_x] == '2')
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

int		ft_sprite_coord(t_cub *scene)
{
	if (scene->s_ray_map_x < 0 || scene->s_ray_map_y < 0 ||
		scene->s_ray_map_x > scene->map_max_x || scene->s_ray_map_y > scene->map_max_y)
		return (0);
	return (1);
}

int		ft_raycaster(t_cub *scene)
{
	double	dist_arr[scene->res_x];
	int 	n = 0; // DEBUG

	printf("------------START_raycaster_segfault_test---------------\n");
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
			while (ft_check_coord(scene) != 0 && ft_check_is_wall_sprite(scene) != 1)
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
			while (ft_check_coord(scene) != 0 && ft_check_is_wall_sprite(scene) != 1)
			{
				// Next possible point
				scene->vi_x = scene->vi_x + scene->vi_dx;
				scene->vi_y = scene->vi_y + scene->vi_dy;
				// Находим координаты на карте и проверяем, есть ли там стена
				scene->ray_map_x = scene->vi_x / 64;
				scene->ray_map_y = scene->vi_y / 64;
			}
			scene->line_len_v = ft_line_len(scene->vi_y, scene->vi_x, scene);
		}
		else
			scene->line_len_v = 0;

		//Calculating offset for the texture
		if (scene->line_len_h < scene->line_len_v)
		{
			if (scene->dir_y > 0) // 03.07 changed x on y
				scene->offset = (int)scene->hi_x % 64;
			else
				scene->offset = 63 - (int)scene->hi_x % 64;
		}
		else if (scene->line_len_h > scene->line_len_v)
		{
			if (scene->dir_x > 0) // 03.07 поменял y на x
				scene->offset = (int)scene->vi_y % 64;
			else
				scene->offset = 63 - (int)scene->vi_y % 64;
		}

		// Checking what intersection is closer: with horisontal or vertical line?
		if (scene->line_len_h < scene->line_len_v)
		{
			if (scene->line_len_h != 0)
				scene->final_dist = scene->line_len_h;
			else
				scene->final_dist = scene->line_len_v;
		}
		else if (scene->line_len_h > scene->line_len_v)
		{
			if (scene->line_len_v != 0)
				scene->final_dist = scene->line_len_v;
			else
				scene->final_dist = scene->line_len_h;
		}
//	printf("------------2_raycaster_segfault_test---------------\n");
		ft_draw_the_line(scene->plane_x, scene->final_dist, scene);
		dist_arr[scene->plane_x] = scene->final_dist;
		//ft_test_sprites(scene);
		scene->ray_angle -= scene->angle_inc;
		scene->plane_x++;
	}
	//ft_add_sprites(dist_arr, scene);
	ft_sprites(dist_arr, scene);
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

//	printf("---------------read_keys_segfault_test---------------------\n");
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

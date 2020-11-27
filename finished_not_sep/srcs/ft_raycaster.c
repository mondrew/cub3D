/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 00:49:11 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/15 08:50:55 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_ceiling(int x, int y, t_cub *scene)
{
	int ny;

	ny = 0;
	if (y < 0)
		return ;
	while (ny < y)
	{
		if (scene->save_flag == 1)
			scene->array[ny][x] = scene->ceiling_color;
		else
			ft_my_pixel_put(scene, x, ny, scene->ceiling_color);
		ny++;
	}
}

void	ft_draw_floor(int x, int y, t_cub *scene)
{
	while (y < scene->res_y)
	{
		if (scene->save_flag == 1)
			scene->array[y][x] = scene->floor_color;
		else
			ft_my_pixel_put(scene, x, y, scene->floor_color);
		y++;
	}
}

void	ft_draw_wall(int x, int *ry, t_cub *scene)
{
	int i;
	int j;
	int y;

	i = (int)(scene->ki / scene->scale);
	j = scene->offset;
	y = *ry;
	while (i < 64 && scene->ki < scene->size && y < scene->res_y)
	{
		scene->color = *((unsigned int *)(scene->texture + \
				(i * scene->size_line_tex + j * (scene->bpp_tex / 8))));
		if (scene->save_flag == 1)
			scene->array[y][x] = scene->color;
		else
			ft_my_pixel_put(scene, x, y, scene->color);
		y++;
		scene->ki++;
		i = (int)(scene->ki / scene->scale);
	}
	*ry = y;
}

void	ft_set_size(t_cub *scene)
{
	scene->size = scene->final_dist;
	scene->size *= cos(scene->ray_angle - scene->plr_angle);
	scene->size = (64 / scene->size) * scene->dist_to_pp;////////////////
	scene->scale = scene->size / 64;
}

int		ft_get_real_y(t_cub *scene)
{
	int y;

	scene->ki = 0;
	y = (int)((double)scene->res_y / 2 - scene->size / 2);
	while (y < 0)
	{
		y++;
		scene->ki++;
	}
	return (y);
}

int		ft_draw_the_line(int x, t_cub *scene)
{
	int		y;

	ft_set_size(scene);
	y = ft_get_real_y(scene);
	ft_draw_ceiling(x, y, scene);
	if (scene->line_len_h < scene->line_len_v)
	{
		if (scene->dir_y >= 0)
			scene->texture = scene->addr_no_tex;
		if (scene->dir_y < 0)
			scene->texture = scene->addr_so_tex;
	}
	if (scene->line_len_h > scene->line_len_v)
	{
		if (scene->dir_x >= 0)
			scene->texture = scene->addr_ea_tex;
		if (scene->dir_x < 0)
			scene->texture = scene->addr_we_tex;
	}
	ft_draw_wall(x, &y, scene);
	ft_draw_floor(x, y, scene);
	return (0);
}

int		ft_check_wall_sprite(t_cub *scene)
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
		scene->ray_map_x > scene->map_max_x || \
		scene->ray_map_y > scene->map_max_y)
		return (0);
	return (1);
}

void	ft_check_set_angle(char c, t_cub *scene)
{
	if (c == 'p')
	{
		if (scene->plr_angle < 0)
			scene->plr_angle += 2 * PI;
		else if (scene->plr_angle > 2 * PI)
			scene->plr_angle -= 2 * PI;
		scene->ray_angle = scene->plr_angle + PI / 6;
		scene->plane_x = 0;
		scene->mx = 1;
		scene->my = 1;
	}
	else if (c == 'r')
	{
		if (scene->ray_angle < 0)
			scene->ray_angle += 2 * PI;
		else if (scene->ray_angle > 2 * PI)
			scene->ray_angle -= 2 * PI;
	}
}

void	ft_set_ray_dir(t_cub *scene)
{
	if (scene->ray_angle == PI / 2 || scene->ray_angle == 3 * PI / 2)
		scene->dir_x = 0;
	else if ((scene->ray_angle > 3 * PI / 2 && scene->ray_angle <= 2 * PI) || \
			(scene->ray_angle >= 0 && scene->ray_angle < PI / 2))
		scene->dir_x = 1;
	else if ((scene->ray_angle > PI / 2 && scene->ray_angle <= PI) || \
			(scene->ray_angle > PI && scene->ray_angle < 3 * PI / 2))
		scene->dir_x = -1;
	if (scene->ray_angle == 0 || scene->ray_angle == PI || \
			scene->ray_angle == 2 * PI)
		scene->dir_y = 0;
	else if (scene->ray_angle > 0 && scene->ray_angle < PI)
		scene->dir_y = -1;
	else if (scene->ray_angle > PI && scene->ray_angle < 2 * PI)
		scene->dir_y = 1;
}

void	ft_horizontal_intersections(t_cub *scene)
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
			scene->hi_x = scene->hi_x + scene->hi_dx;
			scene->hi_y = scene->hi_y + scene->hi_dy;
			scene->ray_map_x = scene->hi_x / 64;
			scene->ray_map_y = scene->hi_y / 64;
		}
		scene->line_len_h = ft_line_len(scene->hi_y, scene->hi_x, scene);
	}
	else
		scene->line_len_h = 0;
}

void	ft_vertical_intersections(t_cub *scene)
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
			scene->vi_x = scene->vi_x + scene->vi_dx;
			scene->vi_y = scene->vi_y + scene->vi_dy;
			scene->ray_map_x = scene->vi_x / 64;
			scene->ray_map_y = scene->vi_y / 64;
		}
		scene->line_len_v = ft_line_len(scene->vi_y, scene->vi_x, scene);
	}
	else
		scene->line_len_v = 0;
}

void	ft_set_delta(t_cub *scene)
{
	scene->hi_dy = 64 * scene->dir_y;
	if (tan(scene->ray_angle) < 0)
		scene->hi_dx = (-1) * scene->dir_x * 64 / tan(scene->ray_angle);
	else
		scene->hi_dx = scene->dir_x * 64 / tan(scene->ray_angle);
	scene->vi_dx = 64 * scene->dir_x;
	if (tan(scene->ray_angle) < 0)
		scene->vi_dy = (-1) * scene->dir_y * 64 * tan(scene->ray_angle);
	else
		scene->vi_dy = scene->dir_y * 64 * tan(scene->ray_angle);
}

void	ft_offset_dist(t_cub *scene)
{
	if (scene->line_len_h < scene->line_len_v)
	{
		if (scene->dir_y > 0)
			scene->offset = (int)scene->hi_x % 64;
		else
			scene->offset = 63 - (int)scene->hi_x % 64;
		if (scene->line_len_h != 0)
			scene->final_dist = scene->line_len_h;
		else
			scene->final_dist = scene->line_len_v;
	}
	else if (scene->line_len_h > scene->line_len_v)
	{
		if (scene->dir_x > 0)
			scene->offset = (int)scene->vi_y % 64;
		else
			scene->offset = 63 - (int)scene->vi_y % 64;
		if (scene->line_len_v != 0)
			scene->final_dist = scene->line_len_v;
		else
			scene->final_dist = scene->line_len_h;
	}
}

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

void	ft_move_forward(t_cub *scene)
{
	if ((scene->map[(int)(scene->plr_glb_y - 10 * sin(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '1') && \
		(scene->map[(int)(scene->plr_glb_y - 10 * sin(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '2'))
	{
		scene->plr_glb_y -= 10 * sin(scene->plr_angle);
	}
	if ((scene->map[(int)scene->plr_glb_y / 64][(int)(scene->plr_glb_x + \
		10 * cos(scene->plr_angle)) / 64] != '1') && \
		(scene->map[(int)scene->plr_glb_y / 64][(int)(scene->plr_glb_x + \
		10 * cos(scene->plr_angle)) / 64] != '2'))
	{
		scene->plr_glb_x += 10 * cos(scene->plr_angle);
	}
}

void	ft_move_back(t_cub *scene)
{
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
}

void	ft_move_left(t_cub *scene)
{
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
}

void	ft_move_right(t_cub *scene)
{
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
}

int		ft_exit_game(t_cub *scene)
{
	mlx_destroy_image(scene->mlx_ptr, scene->img_ptr);
	mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	ft_free_struct(scene);
	exit(0);
}

int		ft_read_keys(int keycode, t_cub *scene)
{
	if (keycode == ESC)
		ft_exit_game(scene);
	mlx_destroy_image(scene->mlx_ptr, scene->img_ptr);
	scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->res_x, scene->res_y);
	scene->addr = mlx_get_data_addr(scene->img_ptr, &(scene->bpp), \
			&(scene->size_line), &(scene->endian));
	if (keycode == W)
		ft_move_forward(scene);
	else if (keycode == S)
		ft_move_back(scene);
	else if (keycode == A)
		ft_move_left(scene);
	else if (keycode == D)
		ft_move_right(scene);
	else if (keycode == ARROW_LEFT)
		scene->plr_angle += 100 * (PI / 3) / scene->res_x;
	else if (keycode == ARROW_RIGHT)
		scene->plr_angle -= 100 * (PI / 3) / scene->res_x;
	ft_raycaster(scene);
	return (0);
}

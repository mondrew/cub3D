/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 00:49:11 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/23 16:59:24 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mlx.h"
#include "mlx_int.h"
#include "cub3d.h"
#define screen_width 640
#define screen_height 480
#define ESC 65307

int		ft_read_keys(int keycode, t_vars *vars)
{
	if (keycode == W)
	{
		if (scene->map[(int)(pos_x + dir_x)][(int)pos_y] != 1)
			pos_x += dir_x;
		if (scene->map[(int)pos_x][(int)(pos_y + dir_y)] != 1)
			pos_y += dir_y;
	}
	if (keycode == S)
	{
		if (scene->map[(int)(pos_x - dir_x)][(int)pos_y] != 1)
			pos_x -= dir_x;
		if (scene->map[(int)pos_x][(int)(pos_y - dir_y)] != 1)
			pos_y -= dir_y;
	}
	if (keycode == A)
	{
		if (scene->map[(int)(pos_x + dir_x)][(int)pos_y] != 1)
			pos_x += dir_x;
		if (scene->map[(int)pos_x][(int)(pos_y - dir_y)] != 1)
			pos_y -= dir_y;
	}
	if (keycode == D)
	{
		if (scene->map[(int)(pos_x - dir_x)][(int)pos_y] != 1)
			pos_x -= dir_x;
		if (scene->map[(int)pos_x][(int)(pos_y + dir_y)] != 1)
			pos_y += dir_y;
	}
	if (keycode == ARROW_LEFT)
	{
		double old_dir_x = dir_x;
		dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
		dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);
		double old_plane_x = plane_x;
		plane_x = plane_x * cos(rot_speed) - plane_y * sin(rot_speed);
		plane_y = old_plane_x * sin(rot_speed) + plane_y * cos(rot_speed);
	}
	if (keycode == ARROW_RIGHT)
	{
		double old_dir_x = dir_x;
		dir_x = dir_x * cos(-rot_speed) - dir_y * sin(-rot_speed);
		dir_y = old_dir_x * sin(-rot_speed) + dir_y * cos(-rot_speed);
		double old_plane_x = plane_x;
		plane_x = plane_x * cos(-rot_speed) - plane_y * sin(-rot_speed);
		plane_y = old_plane_x * sin(-rot_speed) + plane_y * cos(-rot_speed);
	}
	else if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		exit(0);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;
	int		color;
	double	pos_x; // x starting position
	double	pos_y; // y starting position
	double	dir_x; // initial direction vector (x)
	double	dir_y; // initial direction vector (y)
	double	plane_x; // camera plane (x)
	double	plane_y; // camera plane (y)
	double	time; // time of current frame
	double	old_time; // time of previous frame
	double	camera_x; // x coordinate on the camera plane (-1, 0, +1)
	double	plane_width; // camera plane width
	int		plane_height;
	double	ray_dir_x; // casting ray direction (x)
	double	ray_dir_y; // casting ray direction (y)
	int		x; // current x coordinate on the camera plane
	int		map_x; // current box in the map (x)
	int		map_y; // current box in the map (y)
	double	side_dist_x; // length of ray from current pos to next x or y-side (x)
	double	side_dist_y; // length of ray from current pos to next x or y-side (y)
	double	delta_dist_x; // length of ray from one x or y-side to next x or y-side (x)
	double	delta_dist_y; // length of ray from one x or y-side to next x or y-side (y)
	double	perp_wall_dist;
	int		step_x; // what direction to step in x or y-direction (either +1 or -1) (x)
	int		step_y; // what direction to step in x or y-direction (either +1 or -1) (y)
	int		hit; // was there a wall hit?
	int		side; // was a NS or WE wall hit? (0 for x-side (WE) , 1 for y-side (NS))
	int		line_height;
	int		draw_start;
	int		draw_end;

	pos_x = 22;
	pos_y = 12;
	dir_x = -1;
	dir_y = 0;
	plane_x = 0;
	plane_y = 0.66;
	time = 0;
	old_time = 0;
	plane_width = screen_width;
	x = 0;
	hit = 0;

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, sceen_width, screen_height, "Mondrew3D");

	img.img_ptr = mlx_new_image(vars.mlx_ptr, screen_width, screen_height);
	img.addr = mlx_get_data_addr(img.img_ptr, &(img.bpp), \
			&(img.size_line), &(img.endian));

	while (x < screew_width)
	{
		//Calculate ray position and direction
		camera_x = 2 * x / plane_width - 1; // x-coordinate in camera space
		ray_dir_x = dir_x + plane_x * camera_x;
		ray_dir_y = dir_y + plane_y * camera_x;

		//Which box of the map we're in
		map_x = (int)pos_x;
		map_y = (int)pos_y;

		//Length of ray from one x or y-side to next x or y-side
		delta_dist_x = (ray_dir_y == 0) ? 0 : ((ray_dir_x == 0) ? \
				1 : abs(1 / ray_dir_x));
		delta_dist_y = (ray_dir_x == 0) ? 0 : ((ray_dir_y == 0) ? \
				1 : abs(1 / ray_dir_y));

		//Calculate step and initial side_dist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}

		//Perform DDA
		while (hit == 0)
		{
			//jump to next map square OR in x-direction OR in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y = += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (scene->map[map_y][map_x] > 0)
				hit == 1;
		}

		//Calculate distance prijected on camera direciton
		if (side == 0)
			perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;

		//Calculate height of line to draw on the screen
		line_height = (int)(plane_height / perp_wall_dist);

		//Calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_height / 2 + plane_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + plane_height / 2;
		if (draw_end >= plane_height)
			draw_end = plane_height - 1;
		//Choose wall color
		if (scene->map[map_y][map_x] == 1)
		{
			color = 0x00ff0000;
		}

		//Give x and y sides different brightness
		if (side == 1)
			color = color / 2;
		while (draw_start <= draw_end)
		{
			ft_my_pixel_put(&img, x, draw_start / 2, 0x0000ff00);
			draw_start++;
		}
		x++;
	}
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, img.img_ptr, 0, 0);
	old_time = time;
	time = clock();
	double frame_time = (time - old_time) / 1000.0;
	printf("%f\n", 1.0 / frame_time);
	double move_speed = frame_time * 5.0;
	double rot_speed = frame_time * 3.0;
	mlx_key_hook(vars.win_ptr, ft_close_win, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 02:28:26 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/21 21:44:13 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mlx.h"
#include "mlx_int.h"
#include "cub3d.h"
#define ESC 65307

/*
int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	new_img;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1024, 512, "Mondrew");
	new_img.img_ptr = mlx_new_image(mlx_ptr, 1024, 512);
	new_img.addr = mlx_get_data_addr(new_img.img_ptr, &(new_img.bpp), \
			&(new_img.size_line), &(new_img.endian));
	ft_my_pixel_put(&new_img, 512, 256, 255);
	mlx_put_image_to_window(mlx_ptr, win_ptr, new_img.img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
*/

int		ft_make_rainbow(int *a, int *r, int *g, int *b)
{
	if (*r == 255 && *b == 0 && *g < 255)
		*g += 1;
	else if (*g == 255 && *b == 0 && *r > 0)
		*r -= 1;
	else if (*g == 255 && *r == 0 && *b < 255)
		*b += 1;
	else if (*b == 255 && *r == 0 && *g > 0)
		*g -= 1;
	else if (*b == 255 && *g == 0 && *r < 255)
		*r += 1;
	else if (*r == 255 && *g == 0 && *b > 0)
		*b -= 1;
	return ((*a << 24) | (*r << 16) | (*g << 8) | *b);
}

/*
int		show_coordinates(int keycode, int x, int y, t_vars *vars)
{
	t_data	img;
	int		a;
	int		r;
	int		g;
	int		b;
	int		color;
	int		ny = 0;

	a = 0;
	r = 255;
	g = 0;
	b = 0;
	img.img_ptr = mlx_new_image(vars->mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img_ptr, &(img.bpp), \
			&(img.size_line), &(img.endian));
	while (x < 1920)
	{
		color = ft_make_rainbow(&a, &r, &g, &b);
		ny = y;
		while (ny < 1080)
		{
			ft_my_pixel_put(&img, x, ny, color);
			ny++;
		}
		x++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, img.img_ptr, 0, 0);
	printf("(%d, %d)\n", x, y);
	return (0);
}
*/

int		ft_close_win(int keycode, t_vars *vars)
{
	printf("%d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		exit(0);
	}
	return (0);
}

int		mouse_win(int x, int y, t_vars *vars)
{
	mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, x, y, 0x00fe7f9c);
	printf("It works!!! Let's go for the cake and cookies and sweets!\n \
			Coordinates are: (%d, %d)\n", x, y);
}

int		main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 1920, 1080, "Mondrew");

	img.img_ptr = mlx_new_image(vars.mlx_ptr, 1024, 512);
	img.addr = mlx_get_data_addr(img.img_ptr, &(img.bpp), \
			&(img.size_line), &(img.endian));
	ft_my_pixel_put(&img, 512, 256, 255);
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, img.img_ptr, 0, 0);

	mlx_key_hook(vars.win_ptr, ft_close_win, &vars);
	//mlx_mouse_hook(vars.win_ptr, show_coordinates, &vars);
	printf("(%d, %d)\n", vars.x, vars.y);
	mlx_hook(vars.win_ptr, MotionNotify, PointerMotionMask, mouse_win, &vars);
	//mlx_loop_hook(vars.mlx_ptr, mouse_hook, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}

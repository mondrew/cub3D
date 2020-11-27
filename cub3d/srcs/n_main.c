/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 02:28:26 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/20 12:31:10 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include "cub3d.h"

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		color;

	x = 50;
	y = 60;
	color = 0x00FF0000;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Mondrew");
	img_ptr = mlx_new_image(mlx_ptr, 200, 300);
	img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	((char *)(img_ptr))[y * 4 * size_line + x * (bpp / 8) + 1] = 255;
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 20, 20);
	mlx_loop(mlx_ptr);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:47:37 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 10:17:27 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"
#include "cub3d.h"

int		ft_put_bmp(int fd, t_cub *scene)
{
	int	i;
	int	j;

	i = scene->res_y - 1;
	ft_putstr_fd("Wait, please, saving bmp picture in process...\n", 1);
	while (i >= 0)
	{
		j = 0;
		while (j < scene->res_x)
		{
			scene->color = scene->array[i][j];
			if (((write(fd, &scene->color, 3)) == -1) || \
					(write(fd, &scene->pad, scene->padding) == -1))
			{
				ft_putstr_fd("Error\nwrite() failed\n", 1);
				return (0);
			}
			j++;
		}
		i--;
	}
	return (1);
}

int		ft_write_bmp_header(int fd, t_bfh *file_header, t_bih *info_header)
{
	if (write(fd, &(file_header->bf_type), 2) == -1 || \
		write(fd, &(file_header->bf_size), 4) == -1 || \
		write(fd, &(file_header->bf_reserved1), 2) == -1 || \
		write(fd, &(file_header->bf_reserved2), 2) == -1 || \
		write(fd, &(file_header->bf_offbits), 4) == -1 || \
		write(fd, &info_header->bi_size, 4) == -1 || \
		write(fd, &info_header->bi_width, 4) == -1 || \
		write(fd, &info_header->bi_height, 4) == -1 || \
		write(fd, &info_header->bi_planes, 2) == -1 || \
		write(fd, &info_header->bi_bitcount, 2) == -1 || \
		write(fd, &info_header->bi_compression, 4) == -1 || \
		write(fd, &info_header->bi_sizeimage, 4) == -1 || \
		write(fd, &info_header->bi_x_pelspermeter, 4) == -1 || \
		write(fd, &info_header->bi_y_pelspermeter, 4) == -1 || \
		write(fd, &info_header->bi_clrused, 4) == -1 || \
		write(fd, &info_header->bi_clrimportant, 4) == -1)
		return (0);
	return (1);
}

int		ft_close_file(int fd)
{
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error\nclose() failed\n", 1);
		return (0);
	}
	return (0);
}

void	ft_bmp_structs(t_bfh *file_header, t_bih *info_header, t_cub *scene)
{
	scene->padding = (4 - (scene->res_x * 3) % 4) % 4;
	file_header->bf_type = 0x4d42;
	file_header->bf_size = 14 + 40 + (scene->res_x * 3 + \
		scene->padding) * scene->res_y;
	file_header->bf_reserved1 = 0;
	file_header->bf_reserved2 = 0;
	file_header->bf_offbits = 54;
	info_header->bi_size = 40;
	info_header->bi_width = scene->res_x;
	info_header->bi_height = scene->res_y;
	info_header->bi_planes = 1;
	info_header->bi_bitcount = 24;
	info_header->bi_compression = 0;
	info_header->bi_sizeimage = (scene->res_x * 3 + \
			scene->padding) * scene->res_y;
	info_header->bi_x_pelspermeter = 0;
	info_header->bi_y_pelspermeter = 0;
	info_header->bi_clrused = 16777216;
	info_header->bi_clrimportant = 0;
}

int		ft_create_bmp(t_cub *scene)
{
	t_bfh			file_header;
	t_bih			info_header;
	int				fd;

	ft_bmp_structs(&file_header, &info_header, scene);
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP \
					| S_IROTH)) == -1)
	{
		ft_putstr_fd("Error\nopen() failed\n", 1);
		return (0);
	}
	if (!(ft_write_bmp_header(fd, &file_header, &info_header)))
	{
		ft_putstr_fd("Error\nwrite() failed\n", 1);
		return (ft_close_file(fd));
	}
	if (!(ft_put_bmp(fd, scene)))
		return (ft_close_file(fd));
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error\nclose() failed\n", 1);
		return (0);
	}
	return (1);
}

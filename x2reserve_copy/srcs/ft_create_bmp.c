/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2020/06/30 21:05:22 by mondrew           #+#    #+#             */
/*   updated: 2020/07/01 21:07:33 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

unsigned int	ft_rgb_to_bgr(unsigned int rgb)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = (rgb >> 16) & 255;
	g = (rgb >> 8) & 255;
	b = rgb & 255;
	return ((b << 16) | (g << 8) | r);
}

int		ft_create_bmp(int width, int height, unsigned int **pic)
{
	t_bfh			file_header;
	t_bih			info_header;
	unsigned int	padding;
	int				fd;
	int				i;
	unsigned int	j;
	unsigned char	pad[3] = {0, 0, 0};
	unsigned int	color;

	i = 0;
	padding = (4 - (width * 3) % 4) % 4;
	printf("Padding: %d\n", padding);
	file_header.bf_type = 0x4d42;
	file_header.bf_size = 14 + 40 + (width * 3 + padding) * height;
	file_header.bf_reserved1 = 0;
	file_header.bf_reserved2 = 0;
	file_header.bf_offbits = 54;
	info_header.bi_size = 40;
	info_header.bi_width = width;
	info_header.bi_height = height;
	info_header.bi_planes = 1;
	info_header.bi_bitcount = 24;
	info_header.bi_compression = 0;
	info_header.bi_sizeimage = (width * 3 + padding) * height;
	info_header.bi_x_pelspermeter = 0;
	info_header.bi_y_pelspermeter = 0;
	//info_header.bi_x_pelspermeter = (96 * 5000 + 64) / 127;
	//info_header.bi_y_pelspermeter = (96 * 5000 + 64) / 127;
	info_header.bi_clrused = 16777216;
	info_header.bi_clrimportant = 0;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH)) == -1)
	{
		printf("error\nopen() failed\n");
		return (0);
	}
	write(fd, &file_header.bf_type, 2);
	write(fd, &file_header.bf_size, 4);
	write(fd, &file_header.bf_reserved1, 2);
	write(fd, &file_header.bf_reserved2, 2);
	write(fd, &file_header.bf_offbits, 4);
	write(fd, &info_header, 40);
	i = height - 1;
	printf("i = height - 1 = %d\n", i);
printf("Wait, please, saving bmp picture in process...\n");
	while (i >= 0)
	{
		j = 0;
		while (j < width)
		{
			color = ft_rgb_to_bgr(pic[i][j]);
			write(fd, &color, 3);
			write(fd, pad, padding);
			j++;
		}
		i--;
	}
	if (close(fd) == -1)
	{
		printf("error\nopen() failed\n");
		return (0);
	}
	return (1);
}

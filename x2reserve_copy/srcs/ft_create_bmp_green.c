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

//#include "bitmap.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // delete! for printf!
#define bi_rgb 0

// bitmapfileheader (14 bytes)
typedef struct	s_bitmapfileheader
{
	short int		bf_type; // bm or 0x4d42
	int				bf_size; // size of the file in bytes
	short int		bf_reserved1; // 0
	short int		bf_reserved2; // 0
	unsigned int	bf_offbits; // dist to pixeldata from the beggin of this structure 54 bytes)
}				t_bfh;

// bitmapinfoheader (40 bytes)
typedef struct	s_bitmapinfoheader
{
	unsigned int	bi_size; // size of the structure in bytes (40 for v.3)
	unsigned int	bi_width; // width in pixels
	unsigned int	bi_height;
	short int		bi_planes; // 1
	short int		bi_bitcount; // bits per pixel 24
	unsigned int	bi_compression; // type of compression bi_rgb
	unsigned int	bi_sizeimage; // size of pixel data in bytes =0 if compr = 0
	unsigned int	bi_x_pelspermeter; // pixels per meter (resolution)
	unsigned int	bi_y_pelspermeter; // pixels per meter (resolution)
	unsigned int	bi_clrused; // size of color table in cells 16777216
	unsigned int	bi_clrimportant; // nbr of used colors from beginning = 0 (for all)
}				t_bih;

// bmp file
typedef struct	s_bitmappicture
{
	t_bfh	file_header;
	t_bih	info_header;
	char	*pixel_data;
}				t_bmp;

unsigned int	ft_little_endian(unsigned int n)
{
	unsigned char c1;
	unsigned char c2;
	unsigned char c3;
	unsigned char c4;

	c1 = n & 255;
	c2 = (n >> 8) & 255;
	c3 = (n >> 16) & 255;
	c4 = (n >> 24) & 255;
	return (((unsigned int)c1 << 24) + ((unsigned int)c2 << 16) + ((unsigned int)c3 << 8) + c4);
}

short int	ft_little_endian_short(short int n)
{
	unsigned char c1;
	unsigned char c2;

	c1 = n & 255;
	c2 = (n >> 8) & 255;
	return (((short int)c1 << 8) + c2);
}

int		ft_createbmp(int width, int height, unsigned int **pic)
{
	t_bfh			file_header;
	t_bih			info_header;
	unsigned int	padding;
	int				fd;
	int				i;
	unsigned char	pad[3] = {0, 0, 0};

	i = 0;
	padding = (4 - (width * 3) % 4) % 4; // not 3 but 4
	file_header.bf_type = 0x4d42;
	//file_header.bf_size = ft_little_endian(14 + 40 + (width * 3 + padding) * height); // not 3 but 4
	file_header.bf_size = 14 + 40 + (width * 3 + padding) * height; // not 3 but 4
	printf("%d\n", file_header.bf_size);
	printf("padding: %d\n", padding);
	printf("struct: %ld\n", sizeof(t_bfh));
	printf("short int: %ld\n", sizeof(short int));
	printf("int: %ld\n", sizeof(int));
	printf("unsigned int: %ld\n", sizeof(unsigned int));
	file_header.bf_reserved1 = 0;
	file_header.bf_reserved2 = 0;
	//file_header.bf_offbits = ft_little_endian(54);
	file_header.bf_offbits = 54;

	//info_header.bi_size = ft_little_endian(40);
	info_header.bi_size = 40;
	//info_header.bi_width = ft_little_endian(width);
	info_header.bi_width = width;
	//info_header.bi_height = ft_little_endian(height);
	info_header.bi_height = height;
	//info_header.bi_planes = ft_little_endian(1);
	info_header.bi_planes = 1;
	//info_header.bi_bitcount = ft_little_endian_short(24);
	info_header.bi_bitcount = 24;
	info_header.bi_compression = 0;
	//info_header.bi_sizeimage = ft_little_endian((width * 3 + padding) * height);
	info_header.bi_sizeimage = (width * 3 + padding) * height;
	printf("SIZE_IMG: %d\n", info_header.bi_sizeimage);
	//info_header.bi_x_pelspermeter = ft_little_endian((96 * 5000 + 64) / 127);
	info_header.bi_x_pelspermeter = (96 * 5000 + 64) / 127;
	//info_header.bi_x_pelspermeter = 0;
	//info_header.bi_y_pelspermeter = ft_little_endian((96 * 5000 + 64) / 127);
	info_header.bi_y_pelspermeter = (96 * 5000 + 64) / 127;
	//info_header.bi_y_pelspermeter = 0;
	//info_header.bi_clrused = ft_little_endian(16777216);
	info_header.bi_clrused = 16777216;
	//info_header.bi_clrused = 0;
	info_header.bi_clrimportant = 0;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH)) == -1)
	{
		printf("error\nopen() failed\n");
		return (0);
	}
	// adding file header
	write(fd, &file_header.bf_type, 2);
	write(fd, &file_header.bf_size, 4);
	write(fd, &file_header.bf_reserved1, 2);
	write(fd, &file_header.bf_reserved2, 2);
	write(fd, &file_header.bf_offbits, 4);
	// adding info header
	write(fd, &info_header, 40);
	// adding pixel_data
	
	int j = 0;
	while (pic[i] != NULL)
	{
		j = 0;
		while (pic[i][j] != '\0')
		{
			write(fd, &pic[i][j], 3);
			write(fd, pad, padding);
			j++;
		}
		i++;
	}
	if (close(fd) == -1)
	{
		printf("error\nopen() failed\n");
		return (0);
	}
	printf("SUCCESS\n");
	return (1);
}

void	ft_free_array(unsigned int **array, int max)
{
	int i;

	i = 0;
	if (array == NULL)
		return ;
	while (i <= max)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// Function that takes rgb and return bgr
unsigned int	ft_rgb_to_bgr(unsigned int rgb)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = (rgb >> 16) & 255;
	b = rgb & 255;
	return ((b << 16) | g | r);
}

int		main(void)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	**pic_array;
	unsigned int	i = 0;
	unsigned int	j = 0;
	unsigned int	width = 1920;
	unsigned int	height = 1080;

	red = 0x00770000;
	green = 0x0000ff00;
	blue = 0x00000052;
	if (!(pic_array = malloc(sizeof(unsigned int*) * (height + 1))))
		return (0);
	while (i < height)
	{
		j = 0;
		if (!(pic_array[i] = malloc(sizeof(unsigned int) * (width + 1))))
		{
			ft_free_array(pic_array, i - 1);
			return (0);
		}
		while (j < width)
		{
			pic_array[i][j] = red | green | blue;
			j++;
		}
		pic_array[i][j] = '\0';
		i++;
	}
	pic_array[i] = NULL;
	if (!(ft_createbmp(width, height, pic_array)))
		return (0);
	ft_free_array(pic_array, i - 1);
	return (0);
}

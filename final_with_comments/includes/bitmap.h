/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 19:25:00 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/08 15:28:37 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
#define BITMAP_H

typedef struct		s_bitmapfileheader
{
	short int		bf_type;
	int				bf_size;
	short int		bf_reserved1;
	short int		bf_reserved2;
	unsigned int	bf_offbits;
}					t_bfh;

typedef struct		s_bitmapinfoheader
{
	unsigned int	bi_size;
	unsigned int	bi_width;
	unsigned int	bi_height;
	short int		bi_planes;
	short int		bi_bitcount;
	unsigned int	bi_compression;
	unsigned int	bi_sizeimage;
	unsigned int	bi_x_pelspermeter;
	unsigned int	bi_y_pelspermeter;
	unsigned int	bi_clrused;
	unsigned int	bi_clrimportant;
}					t_bih;

#endif

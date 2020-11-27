/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:59:34 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/21 21:25:10 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "get_next_line.h"

typedef struct	s_data
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_data;

void	ft_my_pixel_put(t_data *img, int x, int y, int color);

typedef struct	s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			x;
	int			y;
}				t_vars;

int		ft_close_win(int keycode, t_vars *vars);

// Parsing

char	*ft_strjoin_free_add_n(char *s1, char *s2);

typedef struct		s_cub
{
	int				res_x;
	int				res_y;
	char			*no_tex;
	char			*so_tex;
	char			*we_tex;
	char			*ea_tex;
	char			*sprite;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				flag_f;
	int				flag_c;
	char			**map;
	int				pos_x;
	int				pos_y;
	char			dest;
	//Угол поворота относительно 0;
}					t_cub;

#endif

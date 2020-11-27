/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:59:34 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/28 13:53:48 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "get_next_line.h"
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "mlx.h"
# include "mlx_int.h"
# define screen_width 640
# define screen_height 480
# define ESC 65307


typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_data;

char	*ft_strjoin_free_add_n(char *s1, char *s2);

typedef struct		s_cub
{
	// Map parsing
	int				res_x; // screen width
	int				res_y; // screen height
	int				screen_x; //real data
	int				screen_y; // real data
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
	int				plr_map_x;
	int				plr_map_y;
	double			plr_angle;
	int				map_max_x;
	int				map_max_y;

	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;

	// Raycasting
	int				grid_size;
	double			plr_glb_x;
	double			plr_glb_y;
	double			fov_angle;
	double			angle_inc;
	double			dist_to_pp;
	double			ray_angle;
	double			hi_x; // First horisontal intersection
	double			hi_y;
	int				ray_map_x; // First horisontal intersection
	int				ray_map_y;
	double			hi_dy; // Delta for horisontal intersections
	double			hi_dx;
	double			vi_x;
	double			vi_y;
	double			vi_dy;
	double			vi_dx;
	int				dir_y; // +1 if going up, -1 if down
	int				dir_x; // +1 if going right, -1 if going left
	double			line_len_h; // Длина столбца, который соответствует расстоянию до гор. стены
	double			line_len_v; // Длина столбца, который соответствует расстоянию до верт. стены
	int				plane_x;
	
	// Images XPM for texture and sprite
	void	*xpm_no_tex;
	void	*xpm_so_tex;
	void	*xpm_we_tex;
	void	*xpm_ea_tex;
	void	*xpm_sprite;
	int		xpm_w;
	int		xpm_h;

}					t_cub;

int		ft_read_keys(int keycode, t_cub *scene);
void	ft_my_pixel_put(t_cub *scene, int x, int y, int color);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:59:34 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/21 22:31:53 by mondrew          ###   ########.fr       */
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

/*
typedef struct	s_data
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_data;

typedef struct	s_vars
{
	int			x;
	int			y;
}				t_vars;
*/

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

	double			pos_x;
	double			pos_y;
	char			dest;

	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;

	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;

	int		color;
	double	dir_x; // initial direction vector (x)
	double	dir_y; // initial direction vector (y)
	double	old_dir_x;
	double	plane_x; // camera plane (x)
	double	plane_y; // camera plane (y)
	double	old_plane_x;
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
	double	frame_time;
	double	move_speed;
	double	rot_speed;

}					t_cub;

int		ft_read_keys(int keycode, t_cub *scene);
void	ft_my_pixel_put(t_cub *scene, int x, int y, int color);

#endif

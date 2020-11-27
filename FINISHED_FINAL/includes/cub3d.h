/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:59:34 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/14 10:57:33 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "mlx_int.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define PI 3.14159265358979

typedef struct		s_cub
{
	int				res_x;
	int				res_y;
	int				screen_x;
	int				screen_y;
	char			*no_tex;
	char			*so_tex;
	char			*we_tex;
	char			*ea_tex;
	char			*texture;
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
	int				save_flag;
	double			plr_glb_x;
	double			plr_glb_y;
	double			dist_to_pp;
	double			ray_angle;
	double			hi_x;
	double			hi_y;
	int				ray_map_x;
	int				ray_map_y;
	double			hi_dy;
	double			hi_dx;
	double			vi_x;
	double			vi_y;
	double			vi_dy;
	double			vi_dx;
	int				dir_y;
	int				dir_x;
	double			line_len_h;
	double			line_len_v;
	int				plane_x;
	unsigned int	color;
	double			ki;
	double			kj;
	double			scale;
	double			size;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
	void			*xpm_no_tex;
	void			*xpm_so_tex;
	void			*xpm_we_tex;
	void			*xpm_ea_tex;
	void			*xpm_sprite;
	int				xpm_w;
	int				xpm_h;
	char			*addr_no_tex;
	char			*addr_so_tex;
	char			*addr_we_tex;
	char			*addr_ea_tex;
	char			*addr_sprite;
	int				bpp_tex;
	int				size_line_tex;
	int				endian_tex;
	int				offset;
	double			final_dist;
	unsigned int	**array;
	unsigned int	padding;
	double			mx;
	double			my;
	unsigned char	pad[3];
}					t_cub;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			angle;
	double			abs_angle;
	double			dist;
	size_t			size;
}					t_sprite;

int					ft_check_coord(t_cub *scene);
int					ft_check_wall_sprite(t_cub *scene);
int					ft_create_bmp(t_cub *scene);
void				ft_draw_sprite(int x, double dist, t_cub *scene, \
									double dist_arr[]);
int					ft_exit_game(t_cub *scene);
int					ft_free_struct(t_cub *scene);
void				ft_my_pixel_put(t_cub *scene, int x, int y, int color);
void				ft_putstr_fd(char *s, int fd);
int					ft_read_keys(int keycode, t_cub *scene);
void				ft_set_delta(t_cub *scene);
void				ft_set_ray_dir(t_cub *scene);
int					ft_sprites(double dist_arr[], t_cub *scene);
char				*ft_strjoin_free_add_n(char *s1, char *s2);

int					ft_win_img(t_cub *scene);
int					ft_get_tex(t_cub *scene);
void				ft_set_scene_null(t_cub *scene);
int					ft_map_max(char c, t_cub *scene);
int					ft_check_args(int ac, char **av);
int					ft_check_file_name(char *str);
int					ft_parse_map(char *file_name, t_cub *scene);
int					ft_fill_cub_struct(char *str, t_cub *scene, int fd);
int					ft_check_scene_res(char *str, t_cub *scene);
int					ft_check_wall_tex(char *str, t_cub *scene);
int					ft_add_tex_addr(char **array, t_cub *scene);
int					ft_add_tex_addr_sprite(char **array, t_cub *scene);
int					ft_check_color(char *str, t_cub *scene);
int					ft_check_rgb(char **array, t_cub *scene, char id);
int					ft_check_rgb_trash(char **array);
int					ft_fill_color(char **array, t_cub *scene, char id);
int					ft_check_map(char *str, t_cub *scene, int fd);
char				*ft_strjoin_add_n(char *s1, const char *s2);
int					ft_check_scene_fullness(t_cub *scene);
int					ft_map_validity(t_cub *scene);
int					ft_index_low(char **map);
int					ft_check_boundaries(char **map, int low);
int					ft_check_map_left_right(char **map, int low);
int					ft_check_map_content(char **map);
int					ft_check_map_logic(char **map, int low);
int					ft_check_map_logic_zero(char **map, int i, int j, int low);
int					ft_check_zero_neightbours(char c);
int					ft_check_map_logic_space(char **map, int i, int j, int low);
int					ft_check_map_spawn(char **map, int flag);
void				ft_add_spawn(t_cub *scene);
double				ft_get_player_angle(char c);
char				*ft_free_str_null(char *s);
int					ft_free_str_if_not_null(char *str);
int					ft_free_struct(t_cub *scene);
void				ft_free_textures(t_cub *scene);
void				ft_free_split(char **array);
void				ft_free_int_array(t_cub *scene, unsigned int **array);

void				ft_draw_ceiling(int x, int y, t_cub *scene);
void				ft_draw_floor(int x, int y, t_cub *scene);
void				ft_draw_wall(int x, int *ry, t_cub *scene);
void				ft_set_size(t_cub *scene);
int					ft_get_real_y(t_cub *scene);
int					ft_draw_the_line(int x, t_cub *scene);
int					ft_check_wall_sprite(t_cub *scene);
double				ft_line_len(double y1, double x1, t_cub *scene);
int					ft_check_coord(t_cub *scene);
void				ft_check_set_angle(char c, t_cub *scene);
void				ft_set_ray_dir(t_cub *scene);
void				ft_horizontal_intersections(t_cub *scene);
void				ft_vertical_intersections(t_cub *scene);
void				ft_set_delta(t_cub *scene);
void				ft_offset_dist(t_cub *scene);
int					ft_exit_game(t_cub *scene);
int					ft_read_keys(int keycode, t_cub *scene);

int					ft_unique(t_sprite sprite[], t_cub *scene);
void				ft_set_size_skip_neg(int *j, int *x, double dist, \
						t_cub *scene);
void				ft_paint_sprite(int x, int y, t_cub *scene);
void				ft_draw_sprite(int x, double dist, t_cub *scene, \
						double dist_arr[]);
void				ft_add_sprite_data(int *i, t_sprite spt[], t_cub *scene);
void				ft_hor_inter_sprite(int *i, t_sprite sprite[], \
						t_cub *scene);
void				ft_ver_inter_sprite(int *i, t_sprite sprite[], \
						t_cub *scene);
void				ft_sprt(int *in, t_sprite sprite[], double dist_arr[], \
						t_cub *scene);
void				ft_set_null_struct(t_sprite sprite[]);
int					ft_set_two(t_cub *scene);
int					ft_raycaster(t_cub *scene);

#endif

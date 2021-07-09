#include "cub3d.h"

static void		ft_move_forward(t_cub *scene)
{
	if ((scene->map[(int)(scene->plr_glb_y - 10 * sin(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '1') && \
		(scene->map[(int)(scene->plr_glb_y - 10 * sin(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '2'))
	{
		scene->plr_glb_y -= 10 * sin(scene->plr_angle);
	}
	if ((scene->map[(int)scene->plr_glb_y / 64][(int)(scene->plr_glb_x + \
		10 * cos(scene->plr_angle)) / 64] != '1') && \
		(scene->map[(int)scene->plr_glb_y / 64][(int)(scene->plr_glb_x + \
		10 * cos(scene->plr_angle)) / 64] != '2'))
	{
		scene->plr_glb_x += 10 * cos(scene->plr_angle);
	}
}

static void		ft_move_back(t_cub *scene)
{
	if ((scene->map[(int)(scene->plr_glb_y + 10 * sin(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '1') && \
		(scene->map[(int)(scene->plr_glb_y + 10 * sin(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '2'))
	{
		scene->plr_glb_y += 10 * sin(scene->plr_angle);
	}
	if ((scene->map[(int)scene->plr_glb_y / 64]\
		[(int)(scene->plr_glb_x - 10 * cos(scene->plr_angle)) / 64] != '1') && \
		(scene->map[(int)scene->plr_glb_y / 64]\
		[(int)(scene->plr_glb_x - 10 * cos(scene->plr_angle)) / 64] != '2'))
	{
		scene->plr_glb_x -= 10 * cos(scene->plr_angle);
	}
}

static void		ft_move_left(t_cub *scene)
{
	if ((scene->map[(int)(scene->plr_glb_y - 10 * cos(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '1') && \
		(scene->map[(int)(scene->plr_glb_y - 10 * cos(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '2'))
	{
		scene->plr_glb_y -= 10 * cos(scene->plr_angle);
	}
	if ((scene->map[(int)scene->plr_glb_y / 64]\
		[(int)(scene->plr_glb_x - 10 * sin(scene->plr_angle)) / 64] != '1') && \
		(scene->map[(int)scene->plr_glb_y / 64]\
		[(int)(scene->plr_glb_x - 10 * sin(scene->plr_angle)) / 64] != '2'))
	{
		scene->plr_glb_x -= 10 * sin(scene->plr_angle);
	}
}

static void		ft_move_right(t_cub *scene)
{
	if ((scene->map[(int)(scene->plr_glb_y + 10 * cos(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '1') && \
		(scene->map[(int)(scene->plr_glb_y + 10 * cos(scene->plr_angle)) / 64]\
		[(int)scene->plr_glb_x / 64] != '2'))
	{
		scene->plr_glb_y += 10 * cos(scene->plr_angle);
	}
	if ((scene->map[(int)scene->plr_glb_y / 64]\
		[(int)(scene->plr_glb_x + 10 * sin(scene->plr_angle)) / 64] != '1') && \
		(scene->map[(int)scene->plr_glb_y / 64]\
		[(int)(scene->plr_glb_x + 10 * sin(scene->plr_angle)) / 64] != '2'))
	{
		scene->plr_glb_x += 10 * sin(scene->plr_angle);
	}
}

int				ft_read_keys(int keycode, t_cub *scene)
{
	if (keycode == ESC)
		ft_exit_game(scene);
	mlx_destroy_image(scene->mlx_ptr, scene->img_ptr);
	scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->res_x, scene->res_y);
	scene->addr = mlx_get_data_addr(scene->img_ptr, &(scene->bpp), \
			&(scene->size_line), &(scene->endian));
	if (keycode == W)
		ft_move_forward(scene);
	else if (keycode == S)
		ft_move_back(scene);
	else if (keycode == A)
		ft_move_left(scene);
	else if (keycode == D)
		ft_move_right(scene);
	else if (keycode == ARROW_LEFT)
		scene->plr_angle += 100 * (PI / 3) / scene->res_x;
	else if (keycode == ARROW_RIGHT)
		scene->plr_angle -= 100 * (PI / 3) / scene->res_x;
	ft_raycaster(scene);
	return (0);
}

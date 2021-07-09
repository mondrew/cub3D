#include "cub3d.h"

void	ft_set_scene_null(t_cub *scene)
{
	scene->res_x = 0;
	scene->res_y = 0;
	scene->no_tex = NULL;
	scene->so_tex = NULL;
	scene->we_tex = NULL;
	scene->ea_tex = NULL;
	scene->sprite = NULL;
	scene->floor_color = 0;
	scene->ceiling_color = 0;
	scene->flag_f = 0;
	scene->flag_c = 0;
	scene->mlx_ptr = NULL;
	scene->win_ptr = NULL;
	scene->img_ptr = NULL;
	scene->map = NULL;
	scene->array = NULL;
	scene->save_flag = 0;
	scene->plane_x = 0;
	scene->offset = 0;
	scene->ki = 0;
	scene->kj = 0;
	scene->pad[0] = 0;
	scene->pad[1] = 0;
	scene->pad[2] = 0;
}

#include "cub3d.h"

void	ft_vertical_intersections(t_cub *scene)
{
	if (scene->dir_x != 0)
	{
		if (scene->dir_x > 0)
			scene->vi_x = ((int)(scene->plr_glb_x / 64)) * 64 + 64;
		if (scene->dir_x < 0)
			scene->vi_x = ((int)(scene->plr_glb_x / 64)) * 64 - 0.0001;
		scene->ray_map_x = scene->vi_x / 64;
		scene->vi_y = scene->plr_glb_y + \
			(scene->plr_glb_x - scene->vi_x) * (tan(scene->ray_angle));
		scene->ray_map_y = scene->vi_y / 64;
		while (ft_check_coord(scene) != 0 && ft_check_wall_sprite(scene) != 1)
		{
			scene->vi_x = scene->vi_x + scene->vi_dx;
			scene->vi_y = scene->vi_y + scene->vi_dy;
			scene->ray_map_x = scene->vi_x / 64;
			scene->ray_map_y = scene->vi_y / 64;
		}
		scene->line_len_v = ft_line_len(scene->vi_y, scene->vi_x, scene);
	}
	else
		scene->line_len_v = 0;
}

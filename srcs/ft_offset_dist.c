#include "cub3d.h"

void	ft_offset_dist(t_cub *scene)
{
	if (scene->line_len_h < scene->line_len_v)
	{
		if (scene->dir_y > 0)
			scene->offset = (int)scene->hi_x % 64;
		else
			scene->offset = 63 - (int)scene->hi_x % 64;
		if (scene->line_len_h != 0)
			scene->final_dist = scene->line_len_h;
		else
			scene->final_dist = scene->line_len_v;
	}
	else if (scene->line_len_h > scene->line_len_v)
	{
		if (scene->dir_x > 0)
			scene->offset = (int)scene->vi_y % 64;
		else
			scene->offset = 63 - (int)scene->vi_y % 64;
		if (scene->line_len_v != 0)
			scene->final_dist = scene->line_len_v;
		else
			scene->final_dist = scene->line_len_h;
	}
}

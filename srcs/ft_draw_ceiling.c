#include "cub3d.h"

void	ft_draw_ceiling(int x, int y, t_cub *scene)
{
	int ny;

	ny = 0;
	if (y < 0)
		return ;
	while (ny < y)
	{
		if (scene->save_flag == 1)
			scene->array[ny][x] = scene->ceiling_color;
		else
			ft_my_pixel_put(scene, x, ny, scene->ceiling_color);
		ny++;
	}
}

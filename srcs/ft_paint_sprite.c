#include "cub3d.h"

void	ft_paint_sprite(int x, int y, t_cub *scene)
{
	if (scene->save_flag == 1 && scene->color != 0x00000000)
		scene->array[y][x] = scene->color;
	else if (scene->color != 0x00000000)
		ft_my_pixel_put(scene, x, y, scene->color);
}

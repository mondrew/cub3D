#include "cub3d.h"

void	ft_my_pixel_put(t_cub *scene, int x, int y, int color)
{
	char	*dst;

	dst = scene->addr + (y * scene->size_line + x * (scene->bpp / 8));
	*((unsigned int*)dst) = color;
}

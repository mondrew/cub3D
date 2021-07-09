#include "cub3d.h"

void	ft_set_delta(t_cub *scene)
{
	scene->hi_dy = 64 * scene->dir_y;
	if (tan(scene->ray_angle) < 0)
		scene->hi_dx = (-1) * scene->dir_x * 64 / tan(scene->ray_angle);
	else
		scene->hi_dx = scene->dir_x * 64 / tan(scene->ray_angle);
	scene->vi_dx = 64 * scene->dir_x;
	if (tan(scene->ray_angle) < 0)
		scene->vi_dy = (-1) * scene->dir_y * 64 * tan(scene->ray_angle);
	else
		scene->vi_dy = scene->dir_y * 64 * tan(scene->ray_angle);
}

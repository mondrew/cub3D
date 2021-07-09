#include "cub3d.h"

void	ft_set_ray_dir(t_cub *scene)
{
	if (scene->ray_angle == PI / 2 || scene->ray_angle == 3 * PI / 2)
		scene->dir_x = 0;
	else if ((scene->ray_angle > 3 * PI / 2 && scene->ray_angle <= 2 * PI) || \
			(scene->ray_angle >= 0 && scene->ray_angle < PI / 2))
		scene->dir_x = 1;
	else if ((scene->ray_angle > PI / 2 && scene->ray_angle <= PI) || \
			(scene->ray_angle > PI && scene->ray_angle < 3 * PI / 2))
		scene->dir_x = -1;
	if (scene->ray_angle == 0 || scene->ray_angle == PI || \
			scene->ray_angle == 2 * PI)
		scene->dir_y = 0;
	else if (scene->ray_angle > 0 && scene->ray_angle < PI)
		scene->dir_y = -1;
	else if (scene->ray_angle > PI && scene->ray_angle < 2 * PI)
		scene->dir_y = 1;
}

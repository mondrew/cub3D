#include "cub3d.h"

void	ft_check_set_angle(char c, t_cub *scene)
{
	if (c == 'p')
	{
		if (scene->plr_angle < 0)
			scene->plr_angle += 2 * PI;
		else if (scene->plr_angle > 2 * PI)
			scene->plr_angle -= 2 * PI;
		scene->ray_angle = scene->plr_angle + PI / 6;
		scene->plane_x = 0;
		scene->mx = 1;
		scene->my = 1;
	}
	else if (c == 'r')
	{
		if (scene->ray_angle < 0)
			scene->ray_angle += 2 * PI;
		else if (scene->ray_angle > 2 * PI)
			scene->ray_angle -= 2 * PI;
	}
}

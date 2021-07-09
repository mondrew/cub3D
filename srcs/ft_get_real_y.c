#include "cub3d.h"

int		ft_get_real_y(t_cub *scene)
{
	int y;

	scene->ki = 0;
	y = (int)((double)scene->res_y / 2 - scene->size / 2);
	while (y < 0)
	{
		y++;
		scene->ki++;
	}
	return (y);
}

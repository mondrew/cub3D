#include "cub3d.h"

int		ft_check_coord(t_cub *scene)
{
	if (scene->ray_map_x < 0 || scene->ray_map_y < 0 ||
		scene->ray_map_x > scene->map_max_x || \
		scene->ray_map_y > scene->map_max_y)
		return (0);
	return (1);
}

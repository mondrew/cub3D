#include "cub3d.h"

int		ft_check_wall_sprite(t_cub *scene)
{
	if (scene->map[scene->ray_map_y][scene->ray_map_x] == '1')
		return (1);
	else if (scene->map[scene->ray_map_y][scene->ray_map_x] == '2')
		return (2);
	return (0);
}

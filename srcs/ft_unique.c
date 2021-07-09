#include "cub3d.h"

int		ft_unique(t_sprite sprite[], t_cub *scene)
{
	int i;

	i = 0;
	while (i < 20)
	{
		if (((sprite[i]).x == (scene->ray_map_x * 64 + 32)) && \
				((sprite[i]).y == (scene->ray_map_y * 64 + 32)))
			return (0);
		i++;
	}
	return (1);
}

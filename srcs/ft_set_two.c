#include "cub3d.h"

int		ft_set_two(t_cub *scene)
{
	int i;

	i = 0;
	scene->plr_glb_x = scene->plr_map_x * 64 + 64 / 2;
	scene->plr_glb_y = scene->plr_map_y * 64 + 64 / 2;
	scene->dist_to_pp = (scene->res_x / 2) / tan(PI / 6);
	scene->map_max_x = ft_map_max('x', scene);
	scene->map_max_y = ft_map_max('y', scene);
	if (!(scene->array = malloc(sizeof(int *) * scene->res_y)))
	{
		ft_putstr_fd("Error\nnot enough memory\n", 1);
		return (ft_free_struct(scene));
	}
	while (i < scene->res_y)
	{
		if (!(scene->array[i] = malloc(sizeof(int) * scene->res_x)))
		{
			ft_putstr_fd("Error\nnot enough memory\n", 1);
			return (ft_free_struct(scene));
		}
		i++;
	}
	return (1);
}

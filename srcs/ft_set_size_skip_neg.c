#include "cub3d.h"

void	ft_set_size_skip_neg(int *j, int *x, double dist, t_cub *scene)
{
	scene->size = dist;
	scene->kj = 0;
	*j = (int)(scene->kj / scene->scale);
	scene->size = (64 / scene->size) * scene->dist_to_pp;
	scene->scale = scene->size / 64;
	*x = *x - scene->size / 2;
	while (*j < 64 && *x < 0 && scene->kj < scene->size && *x < scene->res_x)
	{
		(*x)++;
		scene->kj++;
		*j = (int)(scene->kj / scene->scale);
	}
}

#include "cub3d.h"

int		ft_check_scene_res(char *str, t_cub *scene)
{
	int		i;
	char	**array;

	i = 0;
	if (scene->res_x != 0 || scene->res_y != 0)
		return (0);
	if (!(array = ft_split(str, ' ')))
		return (0);
	while (array[i] != NULL)
		i++;
	if (i != 3)
	{
		ft_free_split(array);
		return (0);
	}
	if (((scene->res_x = ft_atoi(array[1])) < 1) || \
			((scene->res_y = ft_atoi(array[2])) < 1))
	{
		ft_free_split(array);
		return (0);
	}
	ft_free_split(array);
	return (1);
}

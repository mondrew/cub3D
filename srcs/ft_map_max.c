#include "cub3d.h"

int		ft_map_max(char c, t_cub *scene)
{
	int i;
	int len_max;
	int len_curr;

	i = 0;
	len_max = 0;
	if (c == 'x')
	{
		while (scene->map[i] != NULL)
		{
			len_curr = ft_strlen(scene->map[i]);
			if (len_curr > len_max)
				len_max = len_curr;
			i++;
		}
	}
	else
	{
		while (scene->map[len_max] != NULL)
			len_max++;
	}
	return (len_max - 1);
}

#include "cub3d.h"

int		ft_index_low(char **map)
{
	int i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i - 1);
}

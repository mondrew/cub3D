#include "cub3d.h"

int		ft_check_map_spawn(char **map, int flag)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
					map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (!flag)
					flag = 1;
				else
					return (0);
			}
			j++;
		}
		i++;
	}
	if (!flag)
		return (0);
	return (1);
}

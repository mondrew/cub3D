#include "cub3d.h"

int		ft_check_map_logic(char **map, int low)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == ' ' && !(ft_check_map_logic_space(map, i, j, low)))
				return (0);
			else if (map[i][j] == '0' && \
					!(ft_check_map_logic_zero(map, i, j, low)))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

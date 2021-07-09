#include "cub3d.h"

int		ft_check_map_left_right(char **map, int low)
{
	int	i;
	int	j;

	i = 1;
	while (i < low)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (0);
		while (map[i][j + 1] != '\0')
			j++;
		while (map[i][j] == ' ')
			j--;
		if (map[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}

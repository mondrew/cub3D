#include "cub3d.h"

int		ft_check_map_logic_space(char **map, int i, int j, int low)
{
	if (i != 0)
	{
		if (((ft_strlen(map[i - 1]) - 1) < (unsigned int)j) || \
				(map[i - 1][j] != ' ' && map[i - 1][j] != '1'))
			return (0);
	}
	if (i != low)
	{
		if (((ft_strlen(map[i + 1]) - 1) < (unsigned int)j) || \
				(map[i + 1][j] != ' ' && map[i + 1][j] != '1'))
			return (0);
	}
	if (j != 0)
	{
		if (map[i][j - 1] != ' ' && map[i][j - 1] != '1')
			return (0);
	}
	if ((unsigned int)j != (ft_strlen(map[i]) - 1))
	{
		if (map[i][j + 1] != ' ' && map[i][j + 1] != '1')
			return (0);
	}
	return (1);
}

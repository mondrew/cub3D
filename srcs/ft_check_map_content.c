#include "cub3d.h"

int		ft_check_map_content(char **map)
{
	int	i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2' && \
				map[i][j] != ' ' && map[i][j] != 'N' && map[i][j] != 'S' && \
									map[i][j] != 'W' && map[i][j] != 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

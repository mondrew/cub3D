#include "cub3d.h"

int		ft_check_rgb_trash(char **array)
{
	int		i;
	int		j;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[i][j] == ' ')
			j++;
		while (array[i][j] >= '0' && array[i][j] <= '9')
			j++;
		while (array[i][j] == ' ')
			j++;
		if (array[i][j] != '\0')
			return (0);
		i++;
	}
	return (1);
}

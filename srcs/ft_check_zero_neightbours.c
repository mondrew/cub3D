#include "cub3d.h"

int		ft_check_zero_neightbours(char c)
{
	if (c != '0' && c != '1' && c != '2' && \
			c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (0);
	return (1);
}

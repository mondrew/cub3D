#include "cub3d.h"

int		ft_free_str_if_not_null(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (0);
}

#include "cub3d.h"

char	*ft_free_str_null(char *s)
{
	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
	return (NULL);
}

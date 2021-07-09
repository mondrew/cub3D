#include "cub3d.h"

void	ft_free_int_array(t_cub *scene, unsigned int **array)
{
	int i;

	i = 0;
	if (array == NULL)
		return ;
	while (i < scene->res_y)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

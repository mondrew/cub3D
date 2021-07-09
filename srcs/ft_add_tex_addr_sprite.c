#include "cub3d.h"

int		ft_add_tex_addr_sprite(char **array, t_cub *scene)
{
	if (scene->sprite != NULL || !(scene->sprite = ft_strdup(array[1])))
		return (0);
	return (1);
}

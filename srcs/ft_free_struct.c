#include "cub3d.h"

int		ft_free_struct(t_cub *scene)
{
	ft_free_textures(scene);
	if (scene->map != NULL)
		ft_free_split(scene->map);
	if (scene->array != NULL)
		ft_free_int_array(scene, scene->array);
	return (0);
}

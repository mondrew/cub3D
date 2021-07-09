#include "cub3d.h"

int		ft_add_tex_addr(char **array, t_cub *scene)
{
	if (!(ft_strncmp(array[0], "NO", 3)))
	{
		if (scene->no_tex != NULL || !(scene->no_tex = ft_strdup(array[1])))
			return (0);
	}
	else if (!(ft_strncmp(array[0], "SO", 3)))
	{
		if (scene->so_tex != NULL || !(scene->so_tex = ft_strdup(array[1])))
			return (0);
	}
	else if (!(ft_strncmp(array[0], "WE", 3)))
	{
		if (scene->we_tex != NULL || !(scene->we_tex = ft_strdup(array[1])))
			return (0);
	}
	else if (!(ft_strncmp(array[0], "EA", 3)))
	{
		if (scene->ea_tex != NULL || !(scene->ea_tex = ft_strdup(array[1])))
			return (0);
	}
	else if (!(ft_strncmp(array[0], "S", 2)))
		return (ft_add_tex_addr_sprite(array, scene));
	return (1);
}

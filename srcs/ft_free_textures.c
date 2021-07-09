#include "cub3d.h"

void	ft_free_textures(t_cub *scene)
{
	if (scene->no_tex != NULL)
	{
		free(scene->no_tex);
		scene->no_tex = NULL;
	}
	if (scene->so_tex != NULL)
	{
		free(scene->so_tex);
		scene->so_tex = NULL;
	}
	if (scene->we_tex != NULL)
	{
		free(scene->we_tex);
		scene->we_tex = NULL;
	}
	if (scene->ea_tex != NULL)
	{
		free(scene->ea_tex);
		scene->ea_tex = NULL;
	}
}

#include "cub3d.h"

int		ft_check_map(char *str, t_cub *scene, int fd)
{
	char	*new_str;
	char	*tmp_str;

	tmp_str = NULL;
	if (ft_check_scene_fullness(scene) == 1)
	{
		if (!(new_str = ft_strdup(str)))
			return (0);
		if (!(new_str = ft_strjoin_add_n(new_str, "\n")))
			return (0);
		while ((get_next_line(fd, &tmp_str)) > 0)
		{
			if (!(new_str = ft_strjoin_free_add_n(new_str, tmp_str)))
				return (0);
		}
		if (tmp_str != NULL)
			free(tmp_str);
		if (!(scene->map = ft_split(new_str, '\n')))
			return (ft_free_str_if_not_null(new_str));
		ft_free_str_if_not_null(new_str);
	}
	else
		return (0);
	return (ft_map_validity(scene));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cub_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:34:13 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:53:54 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_fill_cub_struct(char *str, t_cub *scene, int fd)
{
	int result;

	result = 1;
	if (!(ft_strncmp(str, "", 1)))
		return (1);
	else if (!(ft_strncmp(str, "R ", 2)))
		result = ft_check_scene_res(str, scene);
	else if (!(ft_strncmp(str, "NO ", 3)) || !(ft_strncmp(str, "SO ", 3)) || \
			!(ft_strncmp(str, "WE ", 3)) || !(ft_strncmp(str, "EA ", 3)) || \
			!(ft_strncmp(str, "S ", 2)))
		result = ft_check_wall_tex(str, scene);
	else if (!(ft_strncmp(str, "F ", 2)) || !(ft_strncmp(str, "C ", 2)))
		result = ft_check_color(str, scene);
	else if (!(ft_check_map(str, scene, fd)))
		return (0);
	if (!result)
		return (0);
	return (1);
}

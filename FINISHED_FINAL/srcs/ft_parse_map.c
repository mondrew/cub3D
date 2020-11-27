/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:34:28 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:54:12 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_parse_map(char *file_name, t_cub *scene)
{
	int		fd;
	char	*str;

	str = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error\nopen() failed\n", 1);
		return (0);
	}
	while ((get_next_line(fd, &str)) > 0)
	{
		if (!(ft_fill_cub_struct(str, scene, fd)))
			return (ft_free_str_if_not_null(str));
		ft_free_str_if_not_null(str);
	}
	ft_free_str_if_not_null(str);
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error\nclose() error\n", 1);
		ft_free_struct(scene);
		return (0);
	}
	return (1);
}

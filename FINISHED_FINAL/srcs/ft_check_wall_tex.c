/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_wall_tex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:33:27 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:53:10 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_wall_tex(char *str, t_cub *scene)
{
	int		i;
	int		fd;
	char	**array;

	i = 0;
	if (!(array = ft_split(str, ' ')))
		return (0);
	while (array[i] != NULL)
		i++;
	if ((i != 2) || ((fd = open(array[1], O_RDONLY)) == -1) || \
			(close(fd) == -1) || !(ft_add_tex_addr(array, scene)))
	{
		ft_free_split(array);
		return (0);
	}
	ft_free_split(array);
	return (1);
}

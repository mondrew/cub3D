/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:35:13 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:55:21 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_map_max(char c, t_cub *scene)
{
	int i;
	int len_max;
	int len_curr;

	i = 0;
	len_max = 0;
	if (c == 'x')
	{
		while (scene->map[i] != NULL)
		{
			len_curr = ft_strlen(scene->map[i]);
			if (len_curr > len_max)
				len_max = len_curr;
			i++;
		}
	}
	else
	{
		while (scene->map[len_max] != NULL)
			len_max++;
	}
	return (len_max - 1);
}

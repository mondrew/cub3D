/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_boundaries.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:29:52 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:47:29 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_boundaries(char **map, int low)
{
	int j;

	j = 0;
	while (map[0][j] != '\0')
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (0);
		j++;
	}
	j = 0;
	while (map[low][j] != '\0')
	{
		if (map[low][j] != '1' && map[low][j] != ' ')
			return (0);
		j++;
	}
	if (!(ft_check_map_left_right(map, low)))
		return (0);
	return (1);
}

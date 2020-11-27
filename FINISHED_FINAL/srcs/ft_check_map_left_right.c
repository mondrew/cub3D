/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_left_right.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:29:36 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:46:37 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_map_left_right(char **map, int low)
{
	int	i;
	int	j;

	i = 1;
	while (i < low)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (0);
		while (map[i][j + 1] != '\0')
			j++;
		while (map[i][j] == ' ')
			j--;
		if (map[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}

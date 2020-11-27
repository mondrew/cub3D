/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:27:05 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:42:53 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_add_spawn(t_cub *scene)
{
	int	i;
	int	j;

	i = 0;
	while (scene->map[i] != NULL)
	{
		j = 0;
		while (scene->map[i][j] != '\0')
		{
			if (scene->map[i][j] == 'N' || scene->map[i][j] == 'S' || \
				scene->map[i][j] == 'W' || scene->map[i][j] == 'E')
			{
				scene->plr_map_y = i;
				scene->plr_map_x = j;
				scene->plr_angle = ft_get_player_angle(scene->map[i][j]);
			}
			j++;
		}
		i++;
	}
}

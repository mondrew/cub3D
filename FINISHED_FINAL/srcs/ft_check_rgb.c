/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:32:16 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:50:58 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_rgb(char **array, t_cub *scene, char id)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	if (i != 3)
	{
		ft_free_split(array);
		return (0);
	}
	if (!(ft_check_rgb_trash(array)))
	{
		ft_free_split(array);
		return (0);
	}
	if (!(ft_fill_color(array, scene, id)))
	{
		ft_free_split(array);
		return (0);
	}
	return (1);
}

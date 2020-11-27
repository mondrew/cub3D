/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:32:26 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:51:46 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_color(char *str, t_cub *scene)
{
	char	id;
	char	**array;

	id = *str;
	str++;
	if (id == 'F')
	{
		if (!(scene->flag_f))
			scene->flag_f = 1;
		else
			return (0);
	}
	if (id == 'C')
	{
		if (!(scene->flag_c))
			scene->flag_c = 1;
		else
			return (0);
	}
	if (!(array = ft_split(str, ',')))
		return (0);
	if (!(ft_check_rgb(array, scene, id)))
		return (0);
	ft_free_split(array);
	return (1);
}

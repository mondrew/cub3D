/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_null_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:25:45 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 15:29:52 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_null_struct(t_sprite sprite[])
{
	int i;

	i = 0;
	while (i < 20)
	{
		sprite[i].x = 0;
		sprite[i].y = 0;
		sprite[i].angle = 0;
		sprite[i].abs_angle = 0;
		sprite[i].dist = 0;
		sprite[i].size = 0;
		i++;
	}
}

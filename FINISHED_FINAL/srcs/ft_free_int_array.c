/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_int_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:26:27 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:39:09 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_int_array(t_cub *scene, unsigned int **array)
{
	int i;

	i = 0;
	if (array == NULL)
		return ;
	while (i < scene->res_y)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

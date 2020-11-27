/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:25:40 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:41:13 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_free_struct(t_cub *scene)
{
	ft_free_textures(scene);
	if (scene->map != NULL)
		ft_free_split(scene->map);
	if (scene->array != NULL)
		ft_free_int_array(scene, scene->array);
	return (0);
}

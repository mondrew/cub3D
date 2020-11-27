/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_tex_addr_sprite.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:32:58 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:52:21 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_add_tex_addr_sprite(char **array, t_cub *scene)
{
	if (scene->sprite != NULL || !(scene->sprite = ft_strdup(array[1])))
		return (0);
	return (1);
}

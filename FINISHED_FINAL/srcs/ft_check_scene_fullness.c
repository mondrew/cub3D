/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_scene_fullness.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:30:38 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:48:33 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_scene_fullness(t_cub *scene)
{
	if (scene->res_x != 0 && scene->res_y != 0 && scene->no_tex != NULL && \
			scene->so_tex != NULL && scene->we_tex != NULL && \
			scene->ea_tex != NULL && scene->sprite != NULL && \
			scene->flag_f != 0 && scene->flag_c != 0)
		return (1);
	return (0);
}

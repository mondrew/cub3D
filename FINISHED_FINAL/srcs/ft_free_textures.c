/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:25:25 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:40:44 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_textures(t_cub *scene)
{
	if (scene->no_tex != NULL)
	{
		free(scene->no_tex);
		scene->no_tex = NULL;
	}
	if (scene->so_tex != NULL)
	{
		free(scene->so_tex);
		scene->so_tex = NULL;
	}
	if (scene->we_tex != NULL)
	{
		free(scene->we_tex);
		scene->we_tex = NULL;
	}
	if (scene->ea_tex != NULL)
	{
		free(scene->ea_tex);
		scene->ea_tex = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:30:24 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:48:11 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_map_validity(t_cub *scene)
{
	int	low;

	low = ft_index_low(scene->map);
	if (!(ft_check_boundaries(scene->map, low)))
		return (ft_free_struct(scene));
	if (!(ft_check_map_content(scene->map)))
		return (ft_free_struct(scene));
	if (!(ft_check_map_logic(scene->map, low)))
		return (ft_free_struct(scene));
	if (!(ft_check_map_spawn(scene->map, 0)))
		return (ft_free_struct(scene));
	ft_add_spawn(scene);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:34:43 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 14:54:34 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_file_name(char *str)
{
	while (*str != '\0')
		str++;
	str = str - 4;
	if (!(ft_strncmp(str, ".cub", 4)))
		return (1);
	else
		ft_putstr_fd("Error\nInvalid file extension\n", 1);
	return (0);
}

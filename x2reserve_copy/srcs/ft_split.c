/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 18:29:07 by mondrew           #+#    #+#             */
/*   Updated: 2020/05/09 12:39:26 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_lets(char const *s, char c)
{
	int	counter;

	counter = 0;
	while (*s != c && *s != '\0')
	{
		counter++;
		s++;
	}
	return (counter);
}

static int	ft_count_words(char const *s, char c)
{
	int		counter;

	counter = 0;
	while (*s != '\0')
	{
		if (*s != c && *s != '\0')
		{
			while (*s != c && *s != '\0')
				s++;
			counter++;
		}
		if (*s != '\0')
			s++;
	}
	return (counter);
}

static int	ft_allocate(char const *s, char c, char **array, int i)
{
	array[i] = malloc(sizeof(char) * (ft_count_lets(s, c) + 1));
	if (array[i] == NULL)
	{
		while (i >= 1)
		{
			free(array[i - 1]);
			i--;
		}
		free(array);
		return (0);
	}
	return (1);
}

static char	**ft_additional(char const *s, char c, char **array)
{
	int i;
	int j;

	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			j = 0;
			if (ft_allocate(s, c, array, i) == 0)
				return (NULL);
			while (*s != c && *s != '\0')
				array[i][j++] = *(s++);
			array[i++][j] = '\0';
		}
	}
	array[i] = NULL;
	return (array);
}

char		**ft_split(char const *s, char c)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	array = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (array == NULL)
		return (NULL);
	array = ft_additional(s, c, array);
	return (array);
}

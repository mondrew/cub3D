/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 13:49:16 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/19 15:27:22 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen_checknl(const char *s, int n)
{
	size_t	i;

	i = 0;
	if (n == 1)
	{
		while (s[i] != '\0')
			i++;
		return (i);
	}
	while (*s != '\0')
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char		*ft_strjoin_m(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(new_str = malloc(sizeof(char) * (ft_strlen_checknl(s1, 1) + \
						ft_strlen_checknl(s2, 1) + 1))))
	{
		free(s1);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	i = 0;
	substring = NULL;
	if (s == NULL)
		return (NULL);
	if (len > (ft_strlen_checknl(s, 1) - start))
		len = ft_strlen_checknl(s, 1) - start;
	if (start > ft_strlen_checknl(s, 1))
	{
		if (!(substring = malloc(sizeof(char))))
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	else if (!(substring = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s[start] != '\0' && i < len)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}

char		*ft_itoa_m(int n, int num)
{
	char	*str;
	int		digits;

	digits = 0;
	while (num > 9)
	{
		num = num / 10;
		digits++;
	}
	digits++;
	if (!(str = malloc(sizeof(char) * (digits + 1))))
		return (NULL);
	str[digits] = '\0';
	if (n == 0)
	{
		str[digits - 1] = '0';
		return (str);
	}
	while (n > 0 || (digits == 1 && n == 0 && str[digits - 1] != '-'))
	{
		str[digits-- - 1] = n % 10 + 48;
		n = n / 10;
	}
	return (str);
}

int			ft_atoi(const char *nptr)
{
	unsigned long	nbr;
	int				sign;

	nbr = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' ||
		*nptr == '\f' || *nptr == '\v' || *nptr == '\r')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + *(nptr++) - 48;
		if (sign > 0 && nbr > 9223372036854775807)
			return (-1);
		if (sign < 0 && nbr > 9223372036854775807)
			return (0);
	}
	return ((int)(nbr * sign));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 13:48:09 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/19 15:37:07 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			foo(char **temp_str, t_list **stack, int fd)
{
	t_list	*tmp_lst;

	tmp_lst = *stack;
	*temp_str = ft_substr("", 0, 0);
	if (!(*temp_str))
		ft_lst_del_clear(stack, *stack, 2);
	while (tmp_lst != NULL && *temp_str != NULL)
	{
		if (ft_atoi(tmp_lst->fd) == fd)
		{
			if (!(*temp_str = ft_strjoin_m(*temp_str, tmp_lst->data)))
			{
				ft_lst_del_clear(stack, *stack, 2);
				return (0);
			}
			ft_lst_del_clear(stack, tmp_lst, 1);
			tmp_lst = *stack;
		}
		if (ft_strlen_checknl(*temp_str, 2))
			break ;
		if (tmp_lst != *stack)
			tmp_lst = tmp_lst->next;
	}
	return (!(!(*temp_str)));
}

char		*ft_cut_line(char *str, t_list **stack, int fd)
{
	char	*line;
	char	*to_stack;
	size_t	len_nl;

	len_nl = 0;
	while (str[len_nl] != '\n' && str[len_nl] != '\0')
		len_nl++;
	if ((ft_strlen_checknl(str, 1)) > len_nl + 1)
	{
		if (!(to_stack = ft_substr(str, len_nl + 1, \
						ft_strlen_checknl(str, 1) - len_nl - 1)))
		{
			ft_lst_del_clear(stack, *stack, 2);
			return (NULL);
		}
		if (!(ft_lstnew_addback(stack, fd, to_stack)))
			return (NULL);
	}
	if (!(line = ft_substr(str, 0, len_nl)))
	{
		ft_lst_del_clear(stack, *stack, 2);
		return (NULL);
	}
	return (line);
}

t_list		*ft_lstnew_addback(t_list **stack, int fd, char *to_stack)
{
	t_list	*new;
	t_list	*tmp;

	new = malloc(sizeof(t_list));
	if (!(new) || !((new->fd) = ft_itoa_m(fd, fd)))
	{
		if (new != NULL)
			free(new);
		free(to_stack);
		ft_lst_del_clear(stack, *stack, 2);
		return (NULL);
	}
	new->data = to_stack;
	new->next = NULL;
	if (!(tmp = *stack))
		*stack = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

int			ft_lst_del_clear(t_list **stack, t_list *node, int n)
{
	t_list	*tmp;

	if (!(tmp = *stack))
		return (-1);
	if (*stack == node)
		*stack = node->next;
	else
	{
		while (tmp->next != node)
			tmp = tmp->next;
		tmp->next = node->next;
	}
	free(node->data);
	free(node->fd);
	free(node);
	while (n == 2 && *stack != NULL)
	{
		tmp = *stack;
		*stack = tmp->next;
		free(tmp->data);
		free(tmp->fd);
		free(tmp);
	}
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*stack = NULL;
	char			*temp_str;
	char			buf[BUFFER_SIZE + 1];
	int				ret;

	ret = 1;
	if (BUFFER_SIZE < 1 || !(line) || !(foo(&temp_str, &stack, fd)))
		return (-1);
	while ((!(ft_strlen_checknl(temp_str, 2))) && ret != 0)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) < 0)
		{
			free(temp_str);
			return (ft_lst_del_clear(&stack, stack, 2));
		}
		buf[ret] = '\0';
		if (!(temp_str = ft_strjoin_m(temp_str, buf)))
			return (ft_lst_del_clear(&stack, stack, 2));
	}
	*line = ft_cut_line(temp_str, &stack, fd);
	free(temp_str);
	if (!(*line))
		return (ft_lst_del_clear(&stack, stack, 2));
	return (ret != 0);
}

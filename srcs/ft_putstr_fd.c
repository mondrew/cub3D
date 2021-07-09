#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	str_len;

	str_len = ft_strlen(s);
	if (s == NULL)
		return ;
	if (write(fd, s, str_len) == -1)
		return ;
}

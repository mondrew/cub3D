#include "cub3d.h"

int		ft_check_args(int ac, char **av)
{
	if (ac < 2)
	{
		ft_putstr_fd("Error\nScene configuration file missing\n", 1);
		return (0);
	}
	if (ac > 3)
	{
		ft_putstr_fd("Error\nToo many arguments\n", 1);
		return (0);
	}
	if (!(ft_check_file_name(av[1])))
		return (0);
	if (ac == 3 && !(ft_strncmp(av[2], "--save", 7)))
		return (1);
	else if (ac == 3)
	{
		ft_putstr_fd("Error\nWrong argument\n", 1);
		return (0);
	}
	return (2);
}

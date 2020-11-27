/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:50:38 by mondrew           #+#    #+#             */
/*   Updated: 2020/06/21 01:07:56 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./includes/cub3d.h"

void	ft_free_split(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int		ft_free_struct(t_cub *scene)
{
	if (scene->no_tex != NULL)
		free(scene->no_tex);
	if (scene->so_tex != NULL)
		free(scene->so_tex);
	if (scene->we_tex != NULL)
		free(scene->we_tex);
	if (scene->ea_tex != NULL)
		free(scene->ea_tex);
	if (scene->map != NULL)
		free(scene->map);
	return (0);
	//if struct would be initialized on heap with malloc
	//here should add free(scene)
}

int		ft_free_str_if_not_null(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (0);
}

void	ft_add_spawn(t_cub *scene) // 7.6
{
	int	i;
	int	j;

	i = 0;
	while (scene->map[i] != NULL)
	{
		j = 0;
		while (scene->map[i][j] != '\0')
		{
			if (scene->map[i][j] == 'N' || scene->map[i][j] == 'S' || \
				scene->map[i][j] == 'W' || scene->map[i][j] == 'E')
			{
				scene->pos_y = i;
				scene->pos_x = j;
				scene->dest = scene->map[i][j];
			}
			j++;
		}
		i++;
	}
}

int		ft_check_map_spawn(char **map, int flag) // 7.5
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
					map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (!flag)
					flag = 1;
				else
					return (0);
			}
			j++;
		}
		i++;
	}
	if (!flag)
		return (0);
	return (1);
}

int		ft_check_map_logic_space(char **map, int i, int j, int low) // #7.4.1
{
	if (i != 0) //above Возможно первая проверка лишняя...
	{
		if (((ft_strlen(map[i - 1]) - 1) < (unsigned int)j) || (map[i - 1][j] != ' ' && \
													map[i - 1][j] != '1'))
			return (0);
	}
	if (i != low) //below Возможно первая проверка лишняя
	{
		if (((ft_strlen(map[i + 1]) - 1) < (unsigned int)j) || (map[i + 1][j] != ' ' && \
													map[i + 1][j] != '1'))
			return (0);
	}
	if (j != 0) // left
	{
		if (map[i][j - 1] != ' ' && map[i][j - 1] != '1')
			return (0);
	}
	if ((unsigned int)j != (ft_strlen(map[i]) - 1)) // right
	{
		if (map[i][j + 1] != ' ' && map[i][j + 1] != '1')
			return (0);
	}
	return (1);
}

int		ft_check_zero_neightbours(char c) // #7.4.2.1
{
	if (c != '0' && c != '1' && c != '2' && \
			c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (0);
	return (1);
}

int		ft_check_map_logic_zero(char **map, int i, int j, int low) // #7.4.2
{
	if (i != 0) //above
	{
		if (((ft_strlen(map[i - 1]) - 1) < (unsigned int)j) || \
				!(ft_check_zero_neightbours(map[i - 1][j])))
			return (0);
	}
	if (i != low) //below
	{
		if (((ft_strlen(map[i + 1]) - 1) < (unsigned int)j) || \
				!(ft_check_zero_neightbours(map[i + 1][j])))
			return (0);
	}
	if (j != 0) // left
	{
		if (!(ft_check_zero_neightbours(map[i][j - 1])))
			return (0);
	}
	if ((unsigned int)j != (ft_strlen(map[i]) - 1)) // right
	{
		if (!(ft_check_zero_neightbours(map[i][j + 1])))
			return (0);
	}
	return (1);
}

int 	ft_check_map_logic(char **map, int low) // #7.4
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == ' ' && !(ft_check_map_logic_space(map, i, j, low)))
				return (0);
			else if (map[i][j] == '0' && !(ft_check_map_logic_zero(map, i, j, low)))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_check_map_content(char **map) // #7.3
{
	int	i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2' && \
				map[i][j] != ' ' && map[i][j] != 'N' && map[i][j] != 'S' && \
									map[i][j] != 'W' && map[i][j] != 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_check_map_left_right(char **map, int low) // 7.2.1
{
	int	i;
	int	j;

	i = 1;
	while (i < low)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (0);
		while (map[i][j + 1] != '\0')
			j++;
		while (map[i][j] == ' ')
			j--;
		if (map[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_boundaries(char **map, int low) // #7.2
{
	int j;

	j = 0;
	while (map[0][j] != '\0')
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (0);
		j++;
	}
	while (map[low][j] != '\0')
	{
		if (map[low][j] != '1' && map[low][j] != ' ')
			return (0);
		j++;
	}
	if (!(ft_check_map_left_right(map, low)))
		return (0);
	return (1);
}

int		ft_index_low(char **map) // #7.1
{
	int i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i - 1);
}

int		ft_map_validity(t_cub *scene) // #7
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

int		ft_check_scene_fullness(t_cub *scene) // #6.1
{
	printf("%d\n", scene->res_x);
	printf("%d\n", scene->res_y);
	printf("%s\n", scene->no_tex);
	printf("%s\n", scene->so_tex);
	printf("%s\n", scene->we_tex);
	printf("%s\n", scene->ea_tex);
	printf("%s\n", scene->sprite);
	printf("%d\n", scene->floor_color);
	printf("%d\n", scene->ceiling_color);
	printf("%d\n", scene->flag_f);
	printf("%d\n", scene->flag_c);
	if (scene->res_x != 0 && scene->res_y != 0 && scene->no_tex != NULL && \
			scene->so_tex != NULL && scene->we_tex != NULL && \
			scene->ea_tex != NULL && scene->sprite != NULL && \
			scene->flag_f != 0 && scene->flag_c != 0)
		return (1);
	printf("Hi :-)\n");
	return (0);
}

char	*ft_strjoin_add_n(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2))))
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new_str[i++] = s2[j++];
	new_str[i++] = '\n';
	new_str[i] = '\0';
	free(s1);
	s1 = NULL;
	return (new_str);
}

int		ft_check_map(char *str, t_cub *scene, int fd) // #6
{
	char	*new_str;
	char	*tmp_str;

	tmp_str = NULL;
	if (ft_check_scene_fullness(scene) == 1)
	{
		if (!(new_str = ft_strdup(str)))
			return (0);
		if (!(new_str = ft_strjoin_add_n(new_str, "\n")))
			return (0);
		while ((get_next_line(fd, &tmp_str)) > 0)
		{
			if (!(new_str = ft_strjoin_free_add_n(new_str, tmp_str))) 
				return (0);
		}
		if (tmp_str != NULL)
			free(tmp_str);
		if (!(scene->map = ft_split(new_str, '\n')))
			return (ft_free_str_if_not_null(new_str));
	}
	else
		return (0);
	int i = 0; //////////////////////////////////////////////////////////////////////////
	while (scene->map[i] != NULL)
	{
		printf("---%s\n", scene->map[i]);
		i++;
	}
	return (ft_map_validity(scene));
}

int		ft_fill_color(char **array, t_cub *scene, char id) // #5.1.2
{
	int	a;
	int r;
	int g;
	int b;

	a = 0;
	r = ft_atoi(array[0]);
	g = ft_atoi(array[1]);
	b = ft_atoi(array[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	if (id == 'F')
		scene->floor_color = (a << 24) | (r << 16) | (g << 8) | b;
	if (id == 'C')
		scene->ceiling_color = (a << 24) | (r << 16) | (g << 8) | b;
	return (1);
}

int		ft_check_rgb_trash(char **array) // #5.1.1
{
	int		i;
	int		j;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[i][j] == ' ')
			j++;
		while (array[i][j] >= '0' && array[i][j] <= '9')
			j++;
		while (array[i][j] == ' ')
			j++;
		if (array[i][j] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_rgb(char **array, t_cub *scene, char id) // #5.1
{
	int		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	if (i != 3)
	{
		ft_free_split(array);
		return (0);
	}
	if (!(ft_check_rgb_trash(array)))
	{
		ft_free_split(array);
		return (0);
	}
	if (!(ft_fill_color(array, scene, id)))
	{
		ft_free_split(array);
		return (0);
	}
	return (1);
}

int		ft_check_color(char *str, t_cub *scene) // #5
{
	char	id;
	char	**array;

	id = *str;
	str++;
	if (id == 'F')
	{
		if (!(scene->flag_f))
			scene->flag_f = 1;
		else
			return (0);
	}
	if (id == 'C')
	{
		if (!(scene->flag_c))
			scene->flag_c = 1;
		else
			return (0);
	}
	if (!(array = ft_split(str, ',')))
		return (0);
	if (!(ft_check_rgb(array, scene, id)))
		return (0);
	return (1);
}

int		ft_add_tex_addr_sprite(char **array, t_cub *scene)
{
	if (scene->sprite != NULL || !(scene->sprite = ft_strdup(array[1])))
		return (0);
	return (1);
}

int		ft_add_tex_addr(char **array, t_cub *scene)
{
	if (!(ft_strncmp(array[0], "NO", 3)))
	{
		if (scene->no_tex != NULL || !(scene->no_tex = ft_strdup(array[1])))
			return (0);
	}
	else if (!(ft_strncmp(array[0], "SO", 3)))
	{
		if (scene->so_tex != NULL || !(scene->so_tex = ft_strdup(array[1])))
			return (0);
	}
	else if (!(ft_strncmp(array[0], "WE", 3)))
	{
		if (scene->we_tex != NULL || !(scene->we_tex = ft_strdup(array[1])))
			return (0);
	}
	else if (!(ft_strncmp(array[0], "EA", 3)))
	{
		if (scene->ea_tex != NULL || !(scene->ea_tex = ft_strdup(array[1])))
			return (0);
	}
	else if (!(ft_strncmp(array[0], "S", 2)))
		return (ft_add_tex_addr_sprite(array, scene));
	return (1);
}

int		ft_check_wall_tex(char *str, t_cub *scene) // #4
{
	int		i;
	int		fd;
	char	**array;

	i = 0;
	if (!(array = ft_split(str, ' ')))
		return (0);
	while (array[i] != NULL)
		i++;
	if ((i != 2) || ((fd = open(array[1], O_RDONLY)) == -1) || \
			(close(fd) == -1) || !(ft_add_tex_addr(array, scene)))
	{
		ft_free_split(array);
		return (0);
	}
	ft_free_split(array);
	return (1);
}

int		ft_check_scene_res(char *str, t_cub *scene) // #3
{
	int		i;
	char	**array;

	i = 0;
	if (scene->res_x != 0 || scene->res_y != 0) // Check if already add previously
		return (0);
	if (!(array = ft_split(str, ' ')))
		return (0);
	while (array[i] != NULL)
		i++;
	if (i != 3)
	{
		ft_free_split(array);
		return (0);
	}
	if (((scene->res_x = ft_atoi(array[1])) < 1) || \
			((scene->res_y = ft_atoi(array[2])) < 1))
	{
		ft_free_split(array);
		return (0);
	}
	printf("-----%d\n", scene->res_x);
	printf("-----%d\n", scene->res_y);
	ft_free_split(array);
	return (1);
}

int		ft_fill_cub_struct(char *str, t_cub *scene, int fd) // #2
{
	int result;

	result = 1;
	if (!(ft_strncmp(str, "", 1))) // If the string is empty (it's OK)
		return (1);
	else if (!(ft_strncmp(str, "R ", 2)))
	{
		result = ft_check_scene_res(str, scene);
	}
	else if (!(ft_strncmp(str, "NO ", 3)) || !(ft_strncmp(str, "SO ", 3)) || \
			!(ft_strncmp(str, "WE ", 3)) || !(ft_strncmp(str, "EA ", 3)) || \
			!(ft_strncmp(str, "S ", 2)))
		result = ft_check_wall_tex(str, scene);
	else if (!(ft_strncmp(str, "F ", 2)) || !(ft_strncmp(str, "C ", 2)))
		result = ft_check_color(str, scene); // мб проверка на другое, чтобы в map не пошло г.
	else if (!(ft_check_map(str, scene, fd)))
	{
		printf("--------------WRONG MAP------------~~~~~~\n");
		ft_free_struct(scene);
		return (0);
	}
	if (!result)
	{
		ft_free_struct(scene);
		return (0);
	}
	return (1);
}

int		ft_parse_map(char *file_name, t_cub *scene) // #1
{
	int		fd;
	char	*str;

	str = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		write(1, "Error\nopen() failed\n", 20);
		return (0);
	}
	while ((get_next_line(fd, &str)) > 0)
	{
		if (!(ft_fill_cub_struct(str, scene, fd)))
			return (ft_free_str_if_not_null(str));
		ft_free_str_if_not_null(str);
	}
	ft_free_str_if_not_null(str);
	if (close(fd) == -1)
	{
		write(1, "Error\nclose() error\n", 20);
		ft_free_struct(scene);
		return (0);
	}
	return (1);
}

int		ft_check_file_name(char *str) // #0.1.1
{
	while (*str != '\0')
		str++;
	str = str - 4;
	if (!(ft_strncmp(str, ".cub", 4)))
		return (1);
	else
		write(1, "Error\nInvalid file extension\n", 29);
	return (0);
}

int		ft_check_args(int ac, char **av) // #0.1
{
	if (ac < 2)
	{
		write(1, "Error\nScene configuration file missing\n", 39);
		return (0);
	}
	if (ac > 3)
	{
		write(1, "Error\nToo many arguments\n", 25);
		return (0);
	}
	if (!(ft_check_file_name(av[1])))
		return (0);
	if (ac == 3 && !(ft_strncmp(av[2], "--save", 7)))
		return (1);
	else if (ac == 3)
	{
		write(1, "Error\nWrong argument\n", 21);
		return (0);
	}
	return (2);
}

void	ft_set_scene_null(t_cub *scene)
{
	scene->res_x = 0;
	scene->res_y = 0;
	scene->no_tex = NULL;
	scene->so_tex = NULL;
	scene->we_tex = NULL;
	scene->ea_tex = NULL;
	scene->sprite = NULL;
	scene->floor_color = 0;
	scene->ceiling_color = 0;
	scene->flag_f = 0;
	scene->flag_c = 0;
	scene->map = NULL;
}

int		main(int argc, char **argv) // #0
{
	int		save_flag;
	t_cub	scene;

	ft_set_scene_null(&scene);
	if (!(save_flag = ft_check_args(argc, argv)))
		return (0);
	if (save_flag == 1)
	{
		write(1, "Save_flag works!\n", 17);
		//SAVE RENDER HERE AND DON'T START THE GAME
		return (0);
	}
	if (!(ft_parse_map(argv[1], &scene)))
	{
		write(1, "Error\nInvalid .cub scene configuration file\n", 44);
		return (0);
	}
	return (0);
}

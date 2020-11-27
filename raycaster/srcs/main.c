/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:50:38 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/07 09:00:28 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../includes/cub3d.h"
#include "mlx.h"
#include "mlx_int.h"
#define PI 3.14159

int		ft_raycaster(t_cub *scene);
int		ft_create_bmp(int width, int height, unsigned int **pic);

void	ft_free_int_array(t_cub *scene, unsigned int **array)
{
	int i;

	i = 0;
	if (array == NULL)
		return ;
	while (i < scene->res_y)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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
	if (scene->array != NULL)
		ft_free_int_array(scene, scene->array);
	return (0);
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

double	ft_get_player_angle(char c)
{
	if (c == 'N')
		return (PI / 2);
	else if (c == 'S')
		return (3 * PI / 2);
	else if (c == 'W')
		return (PI);
	else if (c == 'E')
		return (0);
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
				scene->plr_map_y = i;
				scene->plr_map_x = j;
				scene->plr_angle = ft_get_player_angle(scene->map[i][j]);
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
	if (scene->res_x != 0 && scene->res_y != 0 && scene->no_tex != NULL && \
			scene->so_tex != NULL && scene->we_tex != NULL && \
			scene->ea_tex != NULL && scene->sprite != NULL && \
			scene->flag_f != 0 && scene->flag_c != 0)
		return (1);
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

int		ft_map_max(char c, t_cub *scene)
{
	int i;
	int j;
	int len_max;
	int len_curr;

	i = 0;
	len_max = 0;
	if (c == 'x')
	{
		while (scene->map[i] != NULL)
		{
			len_curr = ft_strlen(scene->map[i]);
			if (len_curr > len_max)
				len_max = len_curr;
			i++;
		}
	}
	else
	{
		while (scene->map[len_max] != NULL)
			len_max++;
	}
	return (len_max - 1);
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
	scene->save_flag = 0;
}

int		ft_set_two(t_cub *scene)
{
	int i;

	i = 0;
	scene->plr_glb_x = scene->plr_map_x * 64 + 64 / 2;;
	scene->plr_glb_y = scene->plr_map_y * 64 + 64 / 2;;
	scene->fov_angle = PI / 3;
	scene->angle_inc = scene->fov_angle / scene->res_x;
	scene->dist_to_pp = (scene->res_x / 2) / tan(scene->fov_angle / 2);
	scene->plane_x = 0;
	scene->map_max_x = ft_map_max('x', scene);
	scene->map_max_y = ft_map_max('y', scene);
	scene->offset = 0;
	// Pixel array
	if (!(scene->array = malloc(sizeof(int *) * scene->res_y)))
	{
		//ft_free(scene); ОБЯЗАТЕЛЬНО
		//write Error
		return (1);
	}
	while (i < scene->res_y)
	{
		if (!(scene->array[i] = malloc(sizeof(int) * scene->res_x)))
		{
			//ft_free(scene); ОБЯЗАТЕЛЬНО
			//write Error
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_print_map_sprite(int i, int j, t_cub *scene, t_cub *tmp)
{
	int x1;
	int y1;
	int x2;
	int y2;
	int	lim_x;
	int lim_y;
	int color;

	x1 = j * 64;
	y1 = i * 64; 
	x2 = x1 + 63;
	y2 = y1 + 63;
	lim_x = x1;
	lim_y = y1;
	color = 0x00ff0000;
	while (lim_x < x2)
	{
		lim_y = y1;
		while (lim_y < y2)
		{
			ft_my_pixel_put(tmp, lim_x, lim_y, color);
			lim_y++;
		}
		lim_x++;
	}
	return (0);
}

int		ft_print_map_wall(int i, int j, t_cub *scene, t_cub *tmp)
{
	int x1;
	int y1;
	int x2;
	int y2;
	int	lim_x;
	int lim_y;
	int color;

	x1 = j * 64;
	y1 = i * 64; 
	x2 = x1 + 63;
	y2 = y1 + 63;
	lim_x = x1;
	lim_y = y1;
	color = 0x00ffffff;
	while (lim_x < x2)
	{
		lim_y = y1;
		while (lim_y < y2)
		{
			ft_my_pixel_put(tmp, lim_x, lim_y, color);
			lim_y++;
		}
		lim_x++;
	}
	return (0);
}

int		ft_print_map_empty(int i, int j, t_cub *scene, t_cub *tmp)
{
	int x1;
	int y1;
	int x2;
	int y2;
	int	lim_x;
	int lim_y;
	int color;

	x1 = j * 64;
	y1 = i * 64; 
	x2 = x1 + 63;
	y2 = y1 + 63;
	lim_x = x1;
	lim_y = y1;
	color = 0x00ff0000;
	while (lim_x < x2)
	{
		ft_my_pixel_put(tmp, lim_x, y1, color);
		lim_y++;
	}
	while (lim_y < y2)
	{
		ft_my_pixel_put(tmp, x2, lim_y, color);
		lim_y++;
	}
	lim_x = x2;
	lim_y = y2;
	while (lim_x > x1)
	{
		ft_my_pixel_put(tmp, lim_x, y2, color);
		lim_x--;
	}
	while (lim_y > y1)
	{
		ft_my_pixel_put(tmp, x1, lim_y, color);
		lim_y--;
	}
	return (0);
}

int		ft_print_map(t_cub *scene, t_cub *tmp)
{
	int i;
	int j;

	i = 0;
	while (scene->map[i] != NULL)
	{
		j = 0;
		while (scene->map[i][j] != '\0')
		{
			if (scene->map[i][j] == '1')
				ft_print_map_wall(i, j, scene, tmp);
			else if (scene->map[i][j] == '0' || scene->map[i][j] == 'N' || \
					scene->map[i][j] == 'S' || scene->map[i][j] == 'W' || \
					scene->map[i][j] == 'E')
				ft_print_map_empty(i, j, scene, tmp);
			else if (scene->map[i][j] == '2')
				ft_print_map_sprite(i, j, scene, tmp);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(tmp->mlx_ptr, tmp->win_ptr, tmp->img_ptr, 0, 0);
	return (0);
}

int		main(int argc, char **argv) // #0
{
	t_cub	scene;
	t_cub	tmp;

	ft_set_scene_null(&scene);
	if (!(scene.save_flag = ft_check_args(argc, argv)))
		return (0);
	if (!(ft_parse_map(argv[1], &scene)))
	{
		write(1, "Error\nInvalid .cub scene configuration file\n", 44);
		return (0);
	}

	ft_set_two(&scene);

	write(1, "Configuration file is accepted\n", 31);
	if (!(scene.mlx_ptr = mlx_init())) // if NOT KO (test)
	{
		write(1, "Error\nKO - mlx error\n", 21);
		ft_free_struct(&scene);
		return (0);
	}
	// Check screen size
	mlx_get_screen_size(scene.mlx_ptr, &scene.screen_x, &scene.screen_y);
	printf("res_x: %d\nscreen_x: %d\n", scene.res_x, scene.screen_x);
	printf("res_y: %d\nscreen_y: %d\n", scene.res_y, scene.screen_y);
	if (scene.res_x > scene.screen_x || scene.res_y > scene.screen_y)
	{
		scene.res_x = scene.screen_x;
		scene.res_y = scene.screen_y;
	}

	// Textures
	scene.xpm_no_tex = mlx_xpm_file_to_image(scene.mlx_ptr, scene.no_tex, &scene.xpm_w, &scene.xpm_h);
	scene.addr_no_tex = mlx_get_data_addr(scene.xpm_no_tex, &(scene.bpp_tex), \
			&(scene.size_line_tex), &(scene.endian_tex));
//printf("--------COLOR IMG NO TEX: %x\n", *((unsigned int *)scene.addr_no_tex));

	scene.xpm_so_tex = mlx_xpm_file_to_image(scene.mlx_ptr, scene.so_tex, &scene.xpm_w, &scene.xpm_h);
	scene.addr_so_tex = mlx_get_data_addr(scene.xpm_so_tex, &(scene.bpp_tex), \
			&(scene.size_line_tex), &(scene.endian_tex));
//printf("--------COLOR IMG SO TEX: %x\n", *((unsigned int *)scene.addr_no_tex));
//
	scene.xpm_we_tex = mlx_xpm_file_to_image(scene.mlx_ptr, scene.we_tex, &scene.xpm_w, &scene.xpm_h);
	scene.addr_we_tex = mlx_get_data_addr(scene.xpm_we_tex, &(scene.bpp_tex), \
			&(scene.size_line_tex), &(scene.endian_tex));

	scene.xpm_ea_tex = mlx_xpm_file_to_image(scene.mlx_ptr, scene.ea_tex, &scene.xpm_w, &scene.xpm_h);
	scene.addr_ea_tex = mlx_get_data_addr(scene.xpm_ea_tex, &(scene.bpp_tex), \
			&(scene.size_line_tex), &(scene.endian_tex));

	scene.xpm_sprite = mlx_xpm_file_to_image(scene.mlx_ptr, scene.sprite, &scene.xpm_w, &scene.xpm_h);
	scene.addr_sprite = mlx_get_data_addr(scene.xpm_sprite, &(scene.bpp_tex), \
			&(scene.size_line_tex), &(scene.endian_tex));

	if (scene.save_flag != 1)
	{
	// New window MLX
		scene.win_ptr = mlx_new_window(scene.mlx_ptr, scene.res_x, scene.res_y, "Mondrew3D");

	// MLX main IMAGE
		scene.img_ptr = mlx_new_image(scene.mlx_ptr, scene.res_x, scene.res_y);
		scene.addr = mlx_get_data_addr(scene.img_ptr, &(scene.bpp), \
				&(scene.size_line), &(scene.endian));
	}

	ft_raycaster(&scene);
	if (scene.save_flag == 1)
	{
		write(1, "Screenshot saved\n", 17);
		return (0);
	}

	mlx_key_hook(scene.win_ptr, ft_read_keys, &scene);

/*
	tmp.win_ptr = mlx_new_window(tmp.mlx_ptr, 640, 480, "Map_Mondrew3D");
	tmp.img_ptr = mlx_new_image(tmp.mlx_ptr, 640, 480);
	tmp.addr = mlx_get_data_addr(tmp.img_ptr, &(tmp.bpp), \
			&(tmp.size_line), &(tmp.endian));
	ft_print_map(&scene, &tmp);

	mlx_loop(tmp.mlx_ptr);
*/
	mlx_loop(scene.mlx_ptr);

	return (0);
}

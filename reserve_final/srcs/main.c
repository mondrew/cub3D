/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:50:38 by mondrew           #+#    #+#             */
/*   Updated: 2020/07/13 11:27:12 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	array = NULL;
}

void	ft_free_split(char **array)
{
	int i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

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

int		ft_free_struct(t_cub *scene)
{
	ft_free_textures(scene);
	if (scene->map != NULL)
		ft_free_split(scene->map);
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

void	ft_add_spawn(t_cub *scene)
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

int		ft_check_map_spawn(char **map, int flag)
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

int		ft_check_map_logic_space(char **map, int i, int j, int low)
{
	if (i != 0)
	{
		if (((ft_strlen(map[i - 1]) - 1) < (unsigned int)j) || \
				(map[i - 1][j] != ' ' && map[i - 1][j] != '1'))
			return (0);
	}
	if (i != low)
	{
		if (((ft_strlen(map[i + 1]) - 1) < (unsigned int)j) || \
				(map[i + 1][j] != ' ' && map[i + 1][j] != '1'))
			return (0);
	}
	if (j != 0)
	{
		if (map[i][j - 1] != ' ' && map[i][j - 1] != '1')
			return (0);
	}
	if ((unsigned int)j != (ft_strlen(map[i]) - 1))
	{
		if (map[i][j + 1] != ' ' && map[i][j + 1] != '1')
			return (0);
	}
	return (1);
}

int		ft_check_zero_neightbours(char c)
{
	if (c != '0' && c != '1' && c != '2' && \
			c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (0);
	return (1);
}

int		ft_check_map_logic_zero(char **map, int i, int j, int low)
{
	if (i != 0)
	{
		if (((ft_strlen(map[i - 1]) - 1) < (unsigned int)j) || \
				!(ft_check_zero_neightbours(map[i - 1][j])))
			return (0);
	}
	if (i != low)
	{
		if (((ft_strlen(map[i + 1]) - 1) < (unsigned int)j) || \
				!(ft_check_zero_neightbours(map[i + 1][j])))
			return (0);
	}
	if (j != 0)
	{
		if (!(ft_check_zero_neightbours(map[i][j - 1])))
			return (0);
	}
	if ((unsigned int)j != (ft_strlen(map[i]) - 1))
	{
		if (!(ft_check_zero_neightbours(map[i][j + 1])))
			return (0);
	}
	return (1);
}

int		ft_check_map_logic(char **map, int low)
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
			else if (map[i][j] == '0' && \
					!(ft_check_map_logic_zero(map, i, j, low)))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_check_map_content(char **map)
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

int		ft_check_map_left_right(char **map, int low)
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

int		ft_check_boundaries(char **map, int low)
{
	int j;

	j = 0;
	while (map[0][j] != '\0')
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (0);
		j++;
	}
	j = 0;
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

int		ft_index_low(char **map)
{
	int i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i - 1);
}

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

int		ft_check_scene_fullness(t_cub *scene)
{
	if (scene->res_x != 0 && scene->res_y != 0 && scene->no_tex != NULL && \
			scene->so_tex != NULL && scene->we_tex != NULL && \
			scene->ea_tex != NULL && scene->sprite != NULL && \
			scene->flag_f != 0 && scene->flag_c != 0)
		return (1);
	return (0);
}

char	*ft_free_str_null(char *s)
{
	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
	return (NULL);
}

char	*ft_strjoin_add_n(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (ft_free_str_null(s1));
	if (!(new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2))))
		return (ft_free_str_null(s1));
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

int		ft_check_map(char *str, t_cub *scene, int fd)
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

int		ft_fill_color(char **array, t_cub *scene, char id)
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

int		ft_check_rgb_trash(char **array)
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

int		ft_check_rgb(char **array, t_cub *scene, char id)
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

int		ft_check_color(char *str, t_cub *scene)
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

int		ft_check_wall_tex(char *str, t_cub *scene)
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

int		ft_check_scene_res(char *str, t_cub *scene)
{
	int		i;
	char	**array;

	i = 0;
	if (scene->res_x != 0 || scene->res_y != 0)
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

int		ft_fill_cub_struct(char *str, t_cub *scene, int fd)
{
	int result;

	result = 1;
	if (!(ft_strncmp(str, "", 1)))
		return (1);
	else if (!(ft_strncmp(str, "R ", 2)))
		result = ft_check_scene_res(str, scene);
	else if (!(ft_strncmp(str, "NO ", 3)) || !(ft_strncmp(str, "SO ", 3)) || \
			!(ft_strncmp(str, "WE ", 3)) || !(ft_strncmp(str, "EA ", 3)) || \
			!(ft_strncmp(str, "S ", 2)))
		result = ft_check_wall_tex(str, scene);
	else if (!(ft_strncmp(str, "F ", 2)) || !(ft_strncmp(str, "C ", 2)))
		result = ft_check_color(str, scene);
	else if (!(ft_check_map(str, scene, fd)))
		return (0);
	if (!result)
		return (0);
	return (1);
}

int		ft_parse_map(char *file_name, t_cub *scene)
{
	int		fd;
	char	*str;

	str = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error\nopen() failed\n", 1);
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
		ft_putstr_fd("Error\nclose() error\n", 1);
		ft_free_struct(scene);
		return (0);
	}
	return (1);
}

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

int		ft_map_max(char c, t_cub *scene)
{
	int i;
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
	scene->mlx_ptr = NULL;
	scene->win_ptr = NULL;
	scene->img_ptr = NULL;
	scene->map = NULL;
	scene->array = NULL;
	scene->save_flag = 0;
	scene->plane_x = 0;
	scene->offset = 0;
	scene->ki = 0;
	scene->kj = 0;
	scene->pad[0] = 0;
	scene->pad[1] = 0;
	scene->pad[2] = 0;
}

int		ft_set_two(t_cub *scene)
{
	int i;

	i = 0;
	scene->plr_glb_x = scene->plr_map_x * 64 + 64 / 2;
	scene->plr_glb_y = scene->plr_map_y * 64 + 64 / 2;
	scene->dist_to_pp = (scene->res_x / 2) / tan(PI / 6);
	scene->map_max_x = ft_map_max('x', scene);
	scene->map_max_y = ft_map_max('y', scene);
	if (!(scene->array = malloc(sizeof(int *) * scene->res_y)))
	{
		ft_putstr_fd("Error\nnot enough memory\n", 1);
		return (ft_free_struct(scene));
	}
	while (i < scene->res_y)
	{
		if (!(scene->array[i] = malloc(sizeof(int) * scene->res_x)))
		{
			ft_putstr_fd("Error\nnot enough memory\n", 1);
			return (ft_free_struct(scene));
		}
		i++;
	}
	return (1);
}

int		ft_get_tex(t_cub *scene)
{
	scene->xpm_no_tex = mlx_xpm_file_to_image(scene->mlx_ptr, scene->no_tex, \
			&scene->xpm_w, &scene->xpm_h);
	scene->addr_no_tex = mlx_get_data_addr(scene->xpm_no_tex, \
			&(scene->bpp_tex), &(scene->size_line_tex), &(scene->endian_tex));
	scene->xpm_so_tex = mlx_xpm_file_to_image(scene->mlx_ptr, scene->so_tex, \
			&scene->xpm_w, &scene->xpm_h);
	scene->addr_so_tex = mlx_get_data_addr(scene->xpm_so_tex, \
			&(scene->bpp_tex), &(scene->size_line_tex), &(scene->endian_tex));
	scene->xpm_we_tex = mlx_xpm_file_to_image(scene->mlx_ptr, scene->we_tex, \
			&scene->xpm_w, &scene->xpm_h);
	scene->addr_we_tex = mlx_get_data_addr(scene->xpm_we_tex, \
			&(scene->bpp_tex), &(scene->size_line_tex), &(scene->endian_tex));
	scene->xpm_ea_tex = mlx_xpm_file_to_image(scene->mlx_ptr, scene->ea_tex, \
			&scene->xpm_w, &scene->xpm_h);
	scene->addr_ea_tex = mlx_get_data_addr(scene->xpm_ea_tex, \
			&(scene->bpp_tex), &(scene->size_line_tex), &(scene->endian_tex));
	scene->xpm_sprite = mlx_xpm_file_to_image(scene->mlx_ptr, scene->sprite, \
			&scene->xpm_w, &scene->xpm_h);
	scene->addr_sprite = mlx_get_data_addr(scene->xpm_sprite, \
			&(scene->bpp_tex), &(scene->size_line_tex), &(scene->endian_tex));
	return (1);
}

int		ft_win_img(t_cub *scene)
{
	mlx_get_screen_size(scene->mlx_ptr, &scene->screen_x, &scene->screen_y);
	if (scene->res_x > scene->screen_x)
		scene->res_x = scene->screen_x;
	if (scene->res_y > scene->screen_y)
		scene->res_y = scene->screen_y;
	if (scene->res_x < 10)
		scene->res_x = 10;
	if (scene->res_y < 10)
		scene->res_y = 10;
	if (scene->save_flag != 1)
	{
		scene->win_ptr = mlx_new_window(scene->mlx_ptr, scene->res_x, \
				scene->res_y, "Mondrew3D");
		scene->img_ptr = mlx_new_image(scene->mlx_ptr, scene->res_x, \
				scene->res_y);
		scene->addr = mlx_get_data_addr(scene->img_ptr, &(scene->bpp), \
				&(scene->size_line), &(scene->endian));
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_cub	scene;

	ft_set_scene_null(&scene);
	if (!(scene.save_flag = ft_check_args(argc, argv)))
		return (0);
	if (!(ft_parse_map(argv[1], &scene)))
	{
		ft_putstr_fd("Error\nInvalid .cub scene configuration file\n", 1);
		return (ft_free_struct(&scene));
	}
	if (!(scene.mlx_ptr = mlx_init()))
	{
		ft_putstr_fd("Error\nKO - mlx error\n", 1);
		return (ft_free_struct(&scene));
	}
	if (!(ft_set_two(&scene)) || !(ft_get_tex(&scene)) || !(ft_win_img(&scene)))
		return (ft_free_struct(&scene));
	if (!(ft_raycaster(&scene)) || scene.save_flag == 1)
		return (ft_free_struct(&scene));
	mlx_key_hook(scene.win_ptr, ft_read_keys, &scene);
	mlx_hook(scene.win_ptr, DestroyNotify, StructureNotifyMask, \
			ft_exit_game, &scene);
	mlx_loop(scene.mlx_ptr);
	return (ft_free_struct(&scene));
}

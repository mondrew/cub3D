#include "cub3d.h"

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
	if (!(ft_win_img(&scene)) || !(ft_set_two(&scene)) || !(ft_get_tex(&scene)))
		return (ft_free_struct(&scene));
	if (!(ft_raycaster(&scene)) || scene.save_flag == 1)
		return (ft_free_struct(&scene));
	mlx_key_hook(scene.win_ptr, ft_read_keys, &scene);
	mlx_hook(scene.win_ptr, DestroyNotify, StructureNotifyMask, \
			ft_exit_game, &scene);
	mlx_loop(scene.mlx_ptr);
	return (ft_free_struct(&scene));
}

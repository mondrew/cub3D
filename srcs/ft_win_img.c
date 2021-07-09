#include "cub3d.h"

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

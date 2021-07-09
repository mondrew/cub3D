#include "cub3d.h"

void	ft_sprt(int *in, t_sprite sprite[], double dist_arr[], t_cub *scene)
{
	double	start_angle;
	int		x_sprite;
	int		i;

	i = *in;
	while (i >= 0)
	{
		start_angle = scene->plr_angle - (PI / 6);
		if (start_angle < 0)
			start_angle += 2 * PI;
		if (start_angle > 2 * PI)
			start_angle -= 2 * PI;
		if (sprite[i].abs_angle > 0 && sprite[i].abs_angle < PI / 2 \
				&& start_angle > 3 * PI / 2 && start_angle < 2 * PI)
			sprite[i].abs_angle += 2 * PI;
		if (sprite[i].abs_angle < 2 * PI && sprite[i].abs_angle > 3 * PI / 2 \
				&& start_angle > 0 && start_angle < PI / 2)
			sprite[i].abs_angle -= 2 * PI;
		x_sprite = (double)scene->res_x - ((sprite[i]).abs_angle - \
			start_angle) / (PI / 3) * (double)scene->res_x;
		ft_draw_sprite(x_sprite, (sprite[i]).dist, scene, dist_arr);
		i--;
	}
	*in = i;
}

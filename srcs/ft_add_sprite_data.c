#include "cub3d.h"

void	ft_add_sprite_data(int *i, t_sprite spt[], t_cub *scene)
{
	if (ft_check_coord(scene) != 0 && ft_check_wall_sprite(scene) == 2 && \
			ft_unique(spt, scene) != 0)
	{
		(spt[*i]).x = scene->ray_map_x * 64 + 32;
		(spt[*i]).y = scene->ray_map_y * 64 + 32;
		if ((spt[*i]).x < scene->plr_glb_x)
			scene->mx = -1;
		if ((spt[*i]).y < scene->plr_glb_y)
			scene->my = -1;
		if (((spt[*i]).angle = atan2(scene->my * ((spt[*i]).y - \
		scene->plr_glb_y), scene->mx * ((spt[*i]).x - scene->plr_glb_x))) < 0)
			spt[*i].angle *= -1;
		if ((spt[*i]).x >= scene->plr_glb_x && (spt[*i]).y <= scene->plr_glb_y)
			(spt[*i]).abs_angle = (spt[*i]).angle;
		if ((spt[*i]).x < scene->plr_glb_x && (spt[*i]).y <= scene->plr_glb_y)
			(spt[*i]).abs_angle = PI - (spt[*i]).angle;
		if ((spt[*i]).x <= scene->plr_glb_x && (spt[*i]).y > scene->plr_glb_y)
			(spt[*i]).abs_angle = PI + (spt[*i]).angle;
		if ((spt[*i]).x > scene->plr_glb_x && (spt[*i]).y > scene->plr_glb_y)
			(spt[*i]).abs_angle = 2 * PI - (spt[*i]).angle;
		(spt[*i]).dist = sqrt(pow(scene->plr_glb_x - (spt[*i]).x, 2) + \
			pow(scene->plr_glb_y - (spt[*i]).y, 2));
		(*i)++;
	}
}

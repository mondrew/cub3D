#include "cub3d.h"

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

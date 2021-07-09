NAME = MONDREW_3D
SRCS = 	./srcs/main.c \
		./srcs/ft_my_pixel_put.c \
		./srcs/ft_raycaster.c \
		./srcs/ft_sprites.c \
		./srcs/ft_create_bmp.c \
		./srcs/ft_strjoin_free_all.c \
		./srcs/get_next_line.c \
		./srcs/get_next_line_utils.c \
		./srcs/ft_strlen.c \
		./srcs/ft_strdup.c \
		./srcs/ft_split.c \
		./srcs/ft_putstr_fd.c \
		./srcs/ft_strncmp.c \
		./srcs/ft_check_coord.c \
		./srcs/ft_check_set_angle.c \
		./srcs/ft_check_wall_sprite.c \
		./srcs/ft_draw_sprite.c \
		./srcs/ft_exit_game.c \
		./srcs/ft_free_struct.c \
		./srcs/ft_read_keys.c \
		./srcs/ft_set_delta.c \
		./srcs/ft_set_ray_dir.c \
		./srcs/ft_win_img.c \
		./srcs/ft_get_tex.c \
		./srcs/ft_set_two.c \
		./srcs/ft_set_scene_null.c \
		./srcs/ft_map_max.c \
		./srcs/ft_check_args.c \
		./srcs/ft_check_file_name.c \
		./srcs/ft_parse_map.c \
		./srcs/ft_fill_cub_struct.c \
		./srcs/ft_check_scene_res.c \
		./srcs/ft_check_wall_tex.c \
		./srcs/ft_add_tex_addr.c \
		./srcs/ft_add_tex_addr_sprite.c \
		./srcs/ft_check_color.c \
		./srcs/ft_check_rgb.c \
		./srcs/ft_check_rgb_trash.c \
		./srcs/ft_fill_color.c \
		./srcs/ft_check_map.c \
		./srcs/ft_strjoin_add_n.c \
		./srcs/ft_check_scene_fullness.c \
		./srcs/ft_map_validity.c \
		./srcs/ft_index_low.c \
		./srcs/ft_check_boundaries.c \
		./srcs/ft_check_map_left_right.c \
		./srcs/ft_check_map_content.c \
		./srcs/ft_check_map_logic.c \
		./srcs/ft_check_map_logic_zero.c \
		./srcs/ft_check_zero_neightbours.c \
		./srcs/ft_check_map_logic_space.c \
		./srcs/ft_check_map_spawn.c \
		./srcs/ft_add_spawn.c \
		./srcs/ft_get_player_angle.c \
		./srcs/ft_free_str_null.c \
		./srcs/ft_free_str_if_not_null.c \
		./srcs/ft_free_textures.c \
		./srcs/ft_free_split.c \
		./srcs/ft_free_int_array.c \
		./srcs/ft_draw_ceiling.c \
		./srcs/ft_draw_floor.c \
		./srcs/ft_draw_wall.c \
		./srcs/ft_set_size.c \
		./srcs/ft_get_real_y.c \
		./srcs/ft_draw_the_line.c \
		./srcs/ft_line_len.c \
		./srcs/ft_horizontal_intersections.c \
		./srcs/ft_vertical_intersections.c \
		./srcs/ft_offset_dist.c \
		./srcs/ft_unique.c \
		./srcs/ft_set_size_skip_neg.c \
		./srcs/ft_paint_sprite.c \
		./srcs/ft_add_sprite_data.c \
		./srcs/ft_hor_inter_sprite.c \
		./srcs/ft_ver_inter_sprite.c \
		./srcs/ft_sprt.c \
		./srcs/ft_set_null_struct.c

MLX = ./mlx_linux
INCLUDES = ./includes
INCLIB = /usr/lib
#GGDB3 = -ggdb3

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o) 

.PHONY: all clean fclean re

%.o: %.c
	@gcc $(FLAGS) -I$(INCLIB) -I$(INCLUDES) -I$(MLX) -O3 -c $< -o $@
	@echo "Compiling... Please wait..."

all: $(NAME)

#Linking with the required internal Linux API's
$(NAME): $(OBJS)
	@echo "Compiling ... Please wait..."
	@gcc $(OBJS) -L$(MLX) -lmlx \
		-L$(INCLIB) -lXext -lX11 -lm -lz -lbsd $(GGDB3) -o $(NAME)
	@echo "Compilation successfully done!"

clean:
	@echo "Cleaning object files ..."
	@/bin/rm -f $(OBJS)
	@echo "Object files has been removed!"

fclean: clean
	@echo "Cleaning all ..."
	@/bin/rm -f $(NAME)
	@echo "Everything has been removed!"

re: fclean all

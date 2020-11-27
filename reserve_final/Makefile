# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mondrew <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/10 02:15:42 by mondrew           #+#    #+#              #
#    Updated: 2020/07/13 10:13:42 by mondrew          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
SRCS = ./srcs/main.c \
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
	   ./srcs/ft_strncmp.c

MLX = ./mlx_linux
INCLUDES = ./includes
INCLIB = /usr/lib

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o) 

.PHONY: all clean fclean re

%.o: %.c
	@gcc $(FLAGS) -I$(INCLIB) -I$(INCLUDES) -I$(MLX) -O3 -c $< -o $@

all: $(NAME)

#Linking with the required internal Linux API's
$(NAME): $(OBJS)
	@echo "Compiling ... Please wait..."
	@gcc $(OBJS) -L$(MLX) -lmlx \
		-L$(INCLIB) -lXext -lX11 -lm -lz -lbsd -o $(NAME)
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

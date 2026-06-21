# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:     #
#                                                     +:+ +:+         +:+      #
#    By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/21 21:35:19 by nismayil          #+#    #+#              #
#    Updated: 2026/06/21 21:46:41 by nismayil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all fclean clean val re

NAME=minirt
CC=cc
CFLAGS=-Wall -Wextra -Werror -g

SRCS=minirt.c
OBJS=$(SRCS:%.c=%.o)

LIBFT_DIR=Libft
LIBFT_MAKE=make -C $(LIBFT_DIR)
LIBFT_LIB=$(LIBFT_DIR)/libft.a

# For MacOS
ifeq ($(shell uname), Darwin)
	MLX_DIR=minilibx_macos_metal
	MLX_LIB=$(MLX_DIR)/libmlx.dylib
	LINKS=$(LIBFT_LIB) -L $(MLX_DIR) -lmlx -Wl,-rpath,$(shell pwd)/$(MLX_DIR) -framework OpenGL -framework AppKit
endif

# For Linux
ifeq ($(shell uname), Linux)
	MLX_DIR=minilibx-linux
	MLX_LIB=$(MLX_DIR)/libmlx.a
	LINKS=$(LIBFT_LIB) $(MLX_LIB) -lXext -lX11 -lm -lz
endif

MLX_MAKE=make -C $(MLX_DIR)

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LINKS) -o $(NAME)

$(LIBFT_LIB):
	$(LIBFT_MAKE) all

# For MacOS
ifeq ($(shell uname), Darwin)
$(MLX_LIB):
	$(MLX_MAKE) all
endif

# For Linux
ifeq ($(shell uname), Linux)
$(MLX_LIB):
	$(MLX_MAKE) all
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(LIBFT_MAKE) clean
	$(MLX_MAKE) clean

fclean: clean
	rm -rf $(NAME)
	$(LIBFT_MAKE) fclean

re: fclean all

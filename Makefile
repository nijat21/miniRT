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

.PHONY: all clean fclean re val cl fcl r

NAME=minirt
CC=cc
CFLAGS=-Wall -Wextra -Werror -g -fsanitize=address #-lm
RM=rm -rf
OBJS_DIR=build

INCLUDES:=-I. -I./includes -I./src/Libft 
SRCS:=minirt.c \
				src/parser/parse_ambient.c \
				src/parser/parse_camera.c \
				src/parser/parse_cylinder.c \
				src/parser/parse_light.c \
				src/parser/parse_plane.c \
				src/parser/parse_resolution.c \
				src/parser/parse_sphere.c \
				src/parser/parse_split_spaces.c \
				src/parser/parse_square.c \
				src/parser/parse_triangle.c \
				src/parser/parse_utils.c \
				src/parser/parser.c \
      src/window/win.c \
      src/window/drawer.c \
      src/window/hooks.c \
	  src/vec/vec.c \
	  src/vec/vec_ops.c \
	  src/vec/vec_utils.c \
	  src/vec/vec_comp_ops.c \
	  src/general/utils.c \
	  src/ray/ray.c \
	  src/ray/ray_utils.c \
	  src/ray/intersect.c \
	  src/ray/hit_cylinder.c \
      src/error_handler/error_handler.c 

OBJS:=$(patsubst %.c,$(OBJS_DIR)/%.o, $(SRCS))
VALGRIND = valgrind \
			--leak-check=full \
			--track-fds=yes \
			--show-leak-kinds=all \
			--track-origins=yes \
			--suppressions=readline.supp

LIBFT_DIR=src/Libft
LIBFT_MAKE=make -C $(LIBFT_DIR)
LIBFT_LIB=$(LIBFT_DIR)/libft.a

# For macOS - current setup
ifeq ($(shell uname), Darwin)
	MLX_DIR=minilibx_macos_metal
	MLX_LIB=$(MLX_DIR)/libmlx.dylib
	LINKS=$(LIBFT_LIB) -L$(MLX_DIR) -lmlx  -Wl,-rpath,$(shell pwd)/$(MLX_DIR) -framework OpenGL -framework AppKit
endif

# For Linux - future setup
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
	install_name_tool -id @rpath/libmlx.dylib $(MLX_LIB)
endif

# For Linux
ifeq ($(shell uname), Linux)
$(MLX_LIB):
	$(MLX_MAKE) all
endif

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

val: $(NAME)
	$(VALGRIND) ./$(NAME)
clean:
	$(RM) $(OBJS_DIR)
	$(LIBFT_MAKE) clean
	$(MLX_MAKE) clean

fclean: clean
	$(RM) $(NAME)
	$(LIBFT_MAKE) fclean

re: fclean all

# Development targets
cl:
	$(RM) $(OBJS_DIR)

fcl: cl
	$(RM) $(NAME)

r: fcl all

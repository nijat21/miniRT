/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:27:03 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/21 00:52:27 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# if defined(__APPLE__)
#  include "../minilibx_macos_metal/mlx.h"
# elif defined(__linux__)
#  include "../minilibx-linux/mlx.h"
#  include <X11/keysym.h>
# else
#  error "Unsupported OS"
# endif

# include <minirt.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_pp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_win
{
	void	*win;
}			t_win;

typedef struct s_disp
{
	void	*mlx;
	t_win	*win;
	t_img	*img;
	int		w;
	int		h;
	t_scene	*scene;
}			t_disp;

//---src/window/win.c-----------------------------------------------------
t_disp		*setup_disp(const t_scene *scene, const int width,
				const int height);

//---src/window/hooks.c-----------------------------------------------------
void		cleanup(t_disp *disp);
int			close_win(void *param);
int			key_hook(int keycode, void *param);

//---src/window/drawer.c-----------------------------------------------------
void		color_px(t_disp *disp, int x, int y, t_rgb rgb);

#endif

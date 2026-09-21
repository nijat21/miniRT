/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:54:30 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/21 01:19:36 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>
#include <window.h>

void	cleanup(t_disp *disp)
{
	if (!disp)
		return ;
	if (disp->img)
		mlx_destroy_image(disp->mlx, disp->img->img);
	if (disp->win)
		mlx_destroy_window(disp->mlx, disp->win->win);
	if (disp->mlx)
		mlx_destroy_display(disp->mlx);
	free(disp->img);
	free(disp->win);
	free(disp->mlx);
	free(disp);
}

int	close_win(void *param)
{
	t_disp	*disp;

	disp = (t_disp *)param;
	clean_scene((t_scene *)disp->scene);
	cleanup(disp);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	if (keycode == 53 || keycode == 65307)
		return (close_win((t_disp *)param));
	return (0);
}

// Mouse hook
/* int	mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(),
		void *p; */

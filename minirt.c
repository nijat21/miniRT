/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:52:15 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/21 00:53:39 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/error_handler.h"
#include "includes/minirt.h"
#include "includes/parser.h"
#include "includes/ray.h"
#include "includes/window.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_disp	*disp;
	t_scene	scene;

	if (ac != 2)
		return (print_err(ERR_INPUT_FORMAT), 1);
	if (!parse_scene(av[1], &scene))
		return (print_err(ERR_PARSING_FAILED), 1);
	disp = setup_disp((const t_scene *)&scene, 1280, 720);
	if (!disp)
		return (EXIT_FAILURE);
	if (!shoot_rays(&scene, disp))
	{
		cleanup(disp);
		print_err_msg("Failed to shoot rays.");
		return (EXIT_FAILURE);
	}
	mlx_put_image_to_window(disp->mlx, disp->win->win, disp->img->img, 0, 0);
	mlx_key_hook(disp->win->win, key_hook, disp);
	mlx_hook(disp->win->win, 17, 0, close_win, disp);
	mlx_loop(disp->mlx);
}

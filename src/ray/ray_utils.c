/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:54:06 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/21 16:38:14 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <ray.h>
#include <vec.h>

t_vec	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.orig, vec_scal_mul(ray.dir, t)));
}

// Pinhole viewport
t_vport	vport_init(t_disp *disp, double hfov)
{
	t_vport	vport;

	vport.w = 2 * tan((hfov * M_PI / 180.0) / 2);
	vport.unit = vport.w / disp->w;
	vport.h = disp->h * vport.unit;
	return (vport);
}

t_cam	cam_init(t_cam cam)
{
	t_vec	world;

	world = (t_vec){0, 1, 0};
	if (vec_par_norm(cam.norm, world))
		world = (t_vec){0, 0, 1};
	cam.right = normalize(vec_cross(world, cam.norm));
	cam.up = normalize(vec_cross(cam.norm, cam.right));
	return (cam);
}

bool	before_light(double cur_t, double light_len)
{
	return (cur_t > EPSILON && cur_t < light_len - EPSILON * fmax(1.0,
			light_len));
}

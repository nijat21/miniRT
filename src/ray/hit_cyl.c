/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cyl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:53:59 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 21:51:54 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error_handler.h>
#include <float.h>
#include <math.h>
#include <minirt.h>
#include <ray.h>
#include <utils.h>
#include <vec.h>

bool	side_in_bounds(t_ray ray, t_cyl *cyl, double roots[], double *t)
{
	t_vec	p;
	double	p_proj;
	double	n_axis;
	int		i;

	if (roots[0] > roots[1])
		dbl_swap(&roots[0], &roots[1]);
	n_axis = vec_dot(cyl->cors, cyl->norm);
	i = 0;
	while (i < 2)
	{
		if (roots[i] > EPSILON)
		{
			p = vec_add(ray.orig, vec_scal_mul(ray.dir, roots[i]));
			p_proj = vec_dot(p, cyl->norm);
			if (p_proj >= (n_axis - cyl->h / 2) && p_proj <= (n_axis + cyl->h
					/ 2))
			{
				*t = roots[i];
				return (true);
			}
		}
		i++;
	}
	return (false);
}

double	calc_quad(t_vec ray_perp, t_vec oc_perp, t_cyl *cyl, double roots[])
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = vec_dot(ray_perp, ray_perp);
	if (a < EPSILON)
		return (false);
	b = 2.0 * vec_dot(oc_perp, ray_perp);
	c = vec_dot(oc_perp, oc_perp) - cyl->rad * cyl->rad;
	disc = b * b - 4 * a * c;
	if (disc < 0.0)
		return (false);
	disc = sqrt(disc);
	roots[0] = (-b - disc) / (2 * a);
	roots[1] = (-b + disc) / (2 * a);
	return (true);
}

bool	hit_inf_cyl(t_ray ray, t_cyl *cyl, double roots[], double *t)
{
	t_vec	oc;
	t_vec	oc_perp;
	t_vec	ray_perp;

	oc = vec_sub(ray.orig, cyl->cors);
	oc_perp = vec_sub(oc, vec_scal_mul(cyl->norm, vec_dot(oc, cyl->norm)));
	ray_perp = vec_sub(ray.dir, vec_scal_mul(cyl->norm, vec_dot(ray.dir,
					cyl->norm)));
	if (!calc_quad(ray_perp, oc_perp, cyl, roots))
		return (false);
	return (side_in_bounds(ray, cyl, roots, t));
}

bool	hit_cyl(t_ray ray, t_cyl *cyl, t_cyl_part *part_hit, double *t)
{
	double	roots[2];
	double	side_t;
	double	cap_t;
	bool	p_hits[2];

	p_hits[0] = hit_inf_cyl(ray, cyl, roots, &side_t);
	p_hits[1] = hit_caps(cyl, ray, &cap_t, part_hit);
	if (p_hits[0] && p_hits[1])
		select_cyl_t((double []){side_t, cap_t},
			(t_cyl_part []){SIDE, *part_hit},
			t, part_hit);
	else if (p_hits[1])
		*t = cap_t;
	else if (p_hits[0])
	{
		*t = side_t;
		*part_hit = SIDE;
	}
	else
		return (false);
	return (true);
}

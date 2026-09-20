/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cyl_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:53:56 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 21:50:43 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <minirt.h>
#include <ray.h>
#include <stdbool.h>

bool	select_cyl_t(double ts[], t_cyl_part labels[], double *t,
		t_cyl_part *part_hit)
{
	bool	a_valid;
	bool	b_valid;

	a_valid = ts[0] > EPSILON;
	b_valid = ts[1] > EPSILON;
	if (!a_valid && !b_valid)
		return (false);
	if (a_valid && (!b_valid || ts[0] < ts[1]))
	{
		*t = ts[0];
		*part_hit = labels[0];
	}
	else
	{
		*t = ts[1];
		*part_hit = labels[1];
	}
	return (true);
}

bool	hit_circ_pl(t_ray ray, t_circle cir, double *t)
{
	t_vec	op;
	t_vec	p;
	double	t_tmp;
	double	r_proj;

	r_proj = vec_dot(ray.dir, cir.norm);
	if (fabs(r_proj) < EPSILON)
		return (false);
	op = vec_sub(cir.cors, ray.orig);
	t_tmp = vec_dot(op, cir.norm) / r_proj;
	if (t_tmp < EPSILON)
		return (false);
	p = vec_add(ray.orig, vec_scal_mul(ray.dir, t_tmp));
	if (vec_len(vec_sub(p, cir.cors)) > cir.rad)
		return (false);
	*t = t_tmp;
	return (true);
}

bool	hit_caps(t_cyl *cyl, t_ray ray, double *t, t_cyl_part *part_hit)
{
	t_vec		tmp;
	t_circle	caps[2];
	bool		c_hits[2];
	double		ts[2];

	ts[0] = DBL_MAX;
	ts[1] = DBL_MAX;
	tmp = vec_scal_mul(cyl->norm, (cyl->h / 2));
	caps[0].cors = vec_add(cyl->cors, tmp);
	caps[0].norm = cyl->norm;
	caps[0].rad = cyl->rad;
	caps[1].cors = vec_sub(cyl->cors, tmp);
	caps[1].norm = vec_scal_mul(cyl->norm, -1);
	caps[1].rad = cyl->rad;
	c_hits[0] = hit_circ_pl(ray, caps[0], &ts[0]);
	c_hits[1] = hit_circ_pl(ray, caps[1], &ts[1]);
	if (!c_hits[0] && !c_hits[1])
		return (false);
	return (select_cyl_t(ts, (t_cyl_part[]){TOP, BTM}, t, part_hit));
}

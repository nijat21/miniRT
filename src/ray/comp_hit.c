/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:53:53 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 23:59:09 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error_handler.h>
#include <minirt.h>
#include <ray.h>

t_vec	face_norm(t_vec norm, t_vec ray_dir)
{
	if (vec_dot(norm, ray_dir) > 0)
		return (vec_scal_mul(norm, -1));
	return (norm);
}

t_vec	cyl_surf_norm(t_hit *hit)
{
	t_cyl	*cyl;
	t_vec	close_a;
	t_vec	cyl_norm;
	double	d;

	cyl = ((t_cyl *)hit->obj->data);
	if (hit->part_hit == TOP)
		cyl_norm = cyl->norm;
	else if (hit->part_hit == BTM)
		cyl_norm = vec_scal_mul(cyl->norm, -1);
	else
	{
		d = vec_dot(vec_sub(hit->p, cyl->cors), cyl->norm);
		close_a = vec_add(cyl->cors, vec_scal_mul(cyl->norm, d));
		cyl_norm = normalize(vec_sub(hit->p, close_a));
	}
	return (cyl_norm);
}

bool	surf_norm(t_hit *hit, t_ray ray)
{
	void	*data;

	data = hit->obj->data;
	hit->p = ray_at(ray, hit->t);
	if (hit->obj->type == SPHERE)
	{
		hit->surf_n = face_norm(normalize(vec_sub(hit->p,
						((t_sph *)data)->cors)), ray.dir);
		hit->rgb = ((t_sph *)data)->rgb;
	}
	else if (hit->obj->type == CYLINDER)
	{
		hit->surf_n = face_norm(cyl_surf_norm(hit), ray.dir);
		hit->rgb = ((t_cyl *)hit->obj->data)->rgb;
	}
	else if (hit->obj->type == PLANE)
	{
		hit->surf_n = face_norm(((t_plane *)data)->norm, ray.dir);
		hit->rgb = ((t_plane *)data)->rgb;
	}
	else
		return (print_err(ERR_WRONG_OBJ), false);
	return (true);
}

t_rgb	comp_hit_color(t_scene *scene, t_hit *hit, t_ray ray, bool *err)
{
	t_rgb	res;

	if (!hit->hit)
		res = (t_rgb){0, 0, 0};
	else
	{
		if (!surf_norm(hit, ray))
		{
			*err = true;
			print_err_msg("Failed to compute hit color");
			return ((t_rgb){0, 0, 0});
		}
		res = comp_color((const t_scene *)scene, (const t_hit *)hit);
	}
	return (res);
}

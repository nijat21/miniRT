/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:47 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/21 16:32:54 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <math.h>
# include <window.h>

typedef struct s_vport
{
	double		w;
	double		h;
	double		unit;
}				t_vport;

typedef struct s_ray
{
	t_vec		orig;
	t_vec		dir;
}				t_ray;

typedef enum e_cyl_part
{
	SIDE,
	TOP,
	BTM,
}				t_cyl_part;

typedef struct s_hit
{
	bool		hit;
	double		t;
	t_vec		p;
	t_vec		surf_n;
	t_vec		rgb;
	t_obj		*obj;
	t_cyl_part	part_hit;
}				t_hit;

//---src/ray/ray.c----------------------------
bool			shoot_rays(t_scene *scene, t_disp *disp);

//---src/ray/intersect.c----------------------------
bool			select_t(double t0, double t1, double *t);
bool			hit_sphere(t_ray ray, t_sph sph, double *t1);
bool			hit_plane(t_ray ray, t_plane pl, double *t);
bool			hit_cyl(t_ray ray, t_cyl *cyl, t_cyl_part *part_hit, double *t);

//---src/ray/hit_cyl_utils.c----------------------------
bool			select_cyl_t(double ts[], t_cyl_part labels[], double *t,
					t_cyl_part *part_hit);
bool			hit_circ_pl(t_ray ray, t_circle cir, double *t);
bool			hit_caps(t_cyl *cyl, t_ray ray, double *t,
					t_cyl_part *part_hit);

//---src/ray/comp_hit.c----------------------------
t_rgb			comp_hit_color(t_scene *scene, t_hit *hit, t_ray ray,
					bool *err);

//---src/ray/comp_color.c----------------------------
t_rgb			comp_color(const t_scene *scene, const t_hit *hit);

//---src/ray/ray_utils.c----------------------------
t_cam			cam_init(t_cam cam);
t_vport			vport_init(t_disp *disp, double hfov);
t_vec			ray_at(t_ray ray, double t);
bool			before_light(double cur_t, double light_len);

#endif // RAY_H

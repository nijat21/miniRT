#include <math.h>
#include <minirt.h>
#include <ray.h>
#include <vec.h>
#include <float.h>

bool hit_circ_pl(t_ray ray, t_circle cir, double *t)
{
    t_vec op;
    t_vec p;
    double t_tmp;
    double r_proj;

    r_proj = vec_dot(ray.dir, cir.norm);
    if (fabs(r_proj) < EPSILON)
        return false;
    op = vec_sub(cir.cors, ray.orig);
    t_tmp = vec_dot(op, cir.norm) / r_proj;
    if (t_tmp < EPSILON)
        return false;
    p = vec_add(ray.orig, vec_scal_mul(ray.dir, t_tmp));
    if (vec_len(vec_sub(p, cir.cors)) > cir.rad)
        return false;
    *t = t_tmp;
    return true;
}

bool hit_caps(t_cyl cyl, t_ray ray, double *t)
{
    t_vec tmp;
    t_circle top;
    t_circle btm;
    double top_t;
    double btm_t;
    bool hit_top;
    bool hit_btm;

    top_t = DBL_MAX;
    btm_t = DBL_MAX;
    tmp = vec_scal_mul(cyl.norm, (cyl.h / 2));
    top.cors = vec_add(cyl.cors, tmp);
    top.norm = cyl.norm;
    top.rad = cyl.rad;
    btm.cors = vec_sub(cyl.cors, tmp);
    btm.norm = vec_mul(cyl.norm, (t_vec){-1, -1, -1});
    btm.rad = cyl.rad;
    hit_top = hit_circ_pl(ray, top, &top_t);
    hit_btm = hit_circ_pl(ray, btm, &btm_t);
    if (!hit_top && !hit_btm)
        return false;
    return select_t(top_t, btm_t, t);
}

bool side_in_bounds(t_ray ray, t_cyl cyl, double roots[], double *t)
{
    t_vec p;
    double p_proj;
    double n_axis;
    int i;

    if (roots[0] > roots[1])
        dbl_swap(&roots[0], &roots[1]);
    n_axis = vec_dot(cyl.cors, cyl.norm);
    i = 0;
    while (i < 2)
    {
        if (roots[i] > EPSILON)
        {
            p = vec_add(ray.orig, vec_scal_mul(ray.dir, roots[i]));
            p_proj = vec_dot(p, cyl.norm);
            if (p_proj >= (n_axis - cyl.h / 2) && p_proj <= (n_axis + cyl.h / 2))
            {
                *t = roots[i];
                return true;
            }
        }
        i++;
    }
    return false;
}

bool hit_inf_cyl(t_ray ray, t_cyl cyl, double roots[], double *t)
{
    t_vec oc;
    t_vec oc_perp;
    t_vec ray_perp;
    double a;
    double b;
    double c;
    double disc;
    double sqrt_disc;

    oc = vec_sub(ray.orig, cyl.cors);
    oc_perp = vec_sub(oc, vec_scal_mul(cyl.norm, vec_dot(oc, cyl.norm)));
    ray_perp = vec_sub(ray.dir, vec_scal_mul(cyl.norm, vec_dot(ray.dir, cyl.norm)));
    a = vec_dot(ray_perp, ray_perp);
    if (a < EPSILON)
        return false;
    b = 2.0 * vec_dot(oc_perp, ray_perp);
    c = vec_dot(oc_perp, oc_perp) - cyl.rad * cyl.rad;
    disc = b * b - 4 * a * c;
    if (disc < 0.0)
        return false;
    sqrt_disc = sqrt(disc);
    roots[0] = (-b - sqrt_disc) / (2 * a);
    roots[1] = (-b + sqrt_disc) / (2 * a);
    return side_in_bounds(ray, cyl, roots, t);
}

bool hit_cyl(t_ray ray, t_cyl cyl, double *t)
{
    double roots[2];
    double side_t;
    double cap_t;
    bool h_side;
    bool h_caps;

    h_side = hit_inf_cyl(ray, cyl, roots, &side_t);
    h_caps = hit_caps(cyl, ray, &cap_t);
    if (!h_side && !h_caps)
        return false;
    if (h_side && h_caps)
        select_t(side_t, cap_t, t);
    else if (h_caps)
        *t = cap_t;
    else
        *t = side_t;
    return true;
}

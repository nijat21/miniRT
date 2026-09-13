#include <minirt.h>
#include <ray.h>
#include <error_handler.h>

void cyl_surf_norm(t_hit *hit)
{
    t_cyl *cyl;
    t_vec close_a;
    double d;

    cyl = ((t_cyl *)hit->obj->data);
    if (cyl->part_hit == TOP)
        hit->surf_n = cyl->norm;
    else if (cyl->part_hit == BTM)
        hit->surf_n = vec_scal_mul(cyl->norm, -1);
    else
    {
        d = vec_dot(vec_sub(hit->p, cyl->cors), cyl->norm);
        close_a = vec_add(cyl->cors, vec_scal_mul(cyl->norm, d));
        hit->surf_n = normalize(vec_sub(hit->p, close_a));
    }
}

void surf_norm(t_hit *hit, t_ray ray)
{
    void *data;

    data = hit->obj->data;
    hit->p = ray_at(ray, hit->t);
    if (hit->obj->type == SPHERE)
    {
        hit->surf_n = normalize(vec_sub(hit->p, ((t_sph *)data)->cors));
        hit->rgb = ((t_sph *)data)->rgb;
    }
    else if (hit->obj->type == CYLINDER)
    {
        cyl_surf_norm(hit);
        hit->rgb = ((t_cyl *)hit->obj->data)->rgb;
    }
    else if (hit->obj->type == PLANE)
    {
        hit->surf_n = ((t_plane *)data)->norm;
        hit->rgb = ((t_plane *)data)->rgb;
    }
    else
        def_err();
}

double clamp(double val)
{
    if (val < 0)
    {
        print_err_msg("Color underflow");
        return (0);
    }
    if (val > 255)
    {
        print_err_msg("Color overflow");
        return (255);
    }
    return (val);
}

t_rgb comp_hit_color(t_scene *scene, t_hit *hit, t_ray ray)
{
    t_vec rgb_ratio;
    t_rgb res;

    if (!hit->hit)
        res = (t_rgb){0, 0, 0};
    else
    {
        surf_norm(hit, ray);
        rgb_ratio = comp_color(scene, hit);
        res.r = (int)clamp(rgb_ratio.x * 255);
        res.g = (int)clamp(rgb_ratio.y * 255);
        res.b = (int)clamp(rgb_ratio.z * 255);
    }
    return res;
}

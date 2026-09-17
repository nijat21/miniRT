#include <minirt.h>
#include <ray.h>
#include <error_handler.h>

t_vec face_norm(t_vec norm, t_vec ray_dir)
{
    if (vec_dot(norm, ray_dir) > 0)
        return vec_scal_mul(norm, -1);
    return norm;
}

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
        hit->surf_n = face_norm(((t_plane *)data)->norm, ray.dir);
        hit->rgb = ((t_plane *)data)->rgb;
    }
    else
        def_err();
}

int clamp(double val)
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

t_rgb vec_to_rgb(t_vec rgb_rat)
{
    t_rgb res;

    res.r = clamp(rgb_rat.x * 255);
    res.g = clamp(rgb_rat.y * 255);
    res.b = clamp(rgb_rat.z * 255);
    return res;
}

t_rgb comp_hit_color(t_scene *scene, t_hit *hit, t_ray ray)
{
    t_rgb res;

    if (!hit->hit)
        res = (t_rgb){0, 0, 0};
    else
    {
        surf_norm(hit, ray);
        res = vec_to_rgb(comp_color(scene, hit));
    }
    return res;
}

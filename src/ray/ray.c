#include <math.h>
#include <minirt.h>
#include <ray.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <vec.h>
#include <window.h>
#include <utils.h>
#include <float.h>
#include <error_handler.h>

static void assign_hit(t_hit *hit, t_obj *obj, bool hit_obj, double cur_t)
{
    if (hit_obj)
    {
        if ((cur_t > EPSILON) && (cur_t < hit->t))
        {
            hit->hit = true;
            hit->t = cur_t;
            hit->obj = obj;
        }
    }
}

static bool single_ray(t_hit *hit, t_list *objs, t_ray ray)
{
    double cur_t;
    t_list *tmp;
    t_obj *obj;
    bool res;

    hit->t = DBL_MAX;
    hit->hit = false;
    tmp = objs;
    while (tmp)
    {
        obj = tmp->content;
        if (obj->type == PLANE)
            res = hit_plane(ray, *(t_plane *)obj->data, &cur_t);
        else if (obj->type == SPHERE)
            res = hit_sphere(ray, *(t_sph *)obj->data, &cur_t);
        else if (obj->type == CYLINDER)
            res = hit_cyl(ray, (t_cyl *)obj->data, &cur_t);
        else
            return return_err(ERR_WRONG_OBJ);
        assign_hit(hit, obj, res, cur_t);
        tmp = tmp->next;
    }
    return true;
}

bool shoot_ray(t_disp *disp, t_scene *scene, t_ray ray, double xy[], double ij[])
{
    t_vec right;
    t_vec up;
    t_vec px;
    t_hit hit;

    right = vec_scal_mul(scene->cam.right, xy[0]);
    up = vec_scal_mul(scene->cam.up, xy[1]);
    px = vec_add(vec_add(scene->cam.cors, scene->cam.norm), vec_add(right, up));
    ray.dir = normalize(vec_sub(px, ray.orig));
    if (!single_ray(&hit, scene->objs, ray))
        return false;
    color_px(disp, ij[1], ij[0], comp_hit_color(scene, &hit, ray));
    return true;
}

// shoot rays for each pixel on viewport
bool shoot_rays(t_scene *scene, t_disp *disp)
{
    t_ray ray;
    t_vport vport;
    double ij[2];
    double xy[2];

    scene->cam = cam_init(scene->cam);
    ray.orig = scene->cam.cors;
    vport = vport_init(disp, scene->cam.hfov);
    ij[0] = -1;
    while (++ij[0] < disp->h)
    {
        ij[1] = -1;
        while (++ij[1] < disp->w)
        {
            xy[0] = (ij[1] + 0.5f) * vport.unit - (vport.w / 2);
            xy[1] = (vport.h / 2) - (ij[0] + 0.5f) * vport.unit;
            if (!shoot_ray(disp, scene, ray, xy, ij))
                return false;
        }
    }
    return true;
}

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

    hit->t = DBL_MAX;
    hit->hit = false;
    tmp = objs;
    while (tmp)
    {
        obj = tmp->content;
        if (obj->type == PLANE)
            assign_hit(hit, obj, hit_plane(ray, *(t_plane *)obj->data, &cur_t), cur_t);
        else if (obj->type == SPHERE)
            assign_hit(hit, obj, hit_sphere(ray, *(t_sph *)obj->data, &cur_t), cur_t);
        else if (obj->type == CYLINDER)
            assign_hit(hit, obj, hit_cyl(ray, *(t_cyl *)obj->data, &cur_t), cur_t);
        else
            return return_err(ERR_WRONG_OBJ);
        tmp = tmp->next;
    }
    return true;
}

bool shoot_ray(t_scene scene, t_ray ray, double x, double y)
{
    t_vec right;
    t_vec up;
    t_vec px;
    t_hit hit;

    // Check by rendering images later
    right = vec_scal_mul(scene.cam.right, x);
    up = vec_scal_mul(scene.cam.up, y);
    px = vec_add(vec_add(scene.cam.cors, scene.cam.norm), vec_add(right, up));
    ray.dir = normalize(vec_sub(px, ray.orig));
    if (!single_ray(&hit, scene.objs, ray))
        return false;
    // COLOR THE PIXEL
    return true;
}

// shoot rays for each pixel on viewport
bool shoot_rays(t_scene scene, t_disp *disp)
{
    t_ray ray;
    t_vport vport;
    double i;
    double j;
    double x;
    double y;

    scene.cam = cam_init(scene.cam);
    ray.orig = scene.cam.cors;
    vport = vport_init(disp, scene.cam.hfov);
    i = -1;
    while (++i < disp->h)
    {
        j = -1;
        while (++j < disp->w)
        {
            // camera is in the center and shooting through the middle of the ray
            x = (j + 0.5f) * vport.unit - (vport.w / 2);
            y = (vport.h / 2) - (i + 0.5f) * vport.unit;
            if (!shoot_ray(scene, ray, x, y))
                return false;
            color_px(disp->img, x, y, rgb);
        }
        if (i == 1)
            return 1;
    }
    return true;
}

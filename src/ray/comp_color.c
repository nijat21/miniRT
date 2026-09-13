#include <minirt.h>
#include <ray.h>
#include <vec.h>
#include <error_handler.h>
#include <float.h>

bool interrupted(t_ray ray, t_obj *obj, double lr_len)
{
    double cur_t;

    if (obj->type == PLANE)
    {
        if (hit_plane(ray, *(t_plane *)obj->data, &cur_t) && (cur_t > EPSILON) && (cur_t < lr_len))
            return true;
    }
    else if (obj->type == SPHERE)
    {
        if (hit_sphere(ray, *(t_sph *)obj->data, &cur_t) && (cur_t > EPSILON) && (cur_t < lr_len))
            return true;
    }
    else if (obj->type == CYLINDER)
    {
        if (hit_cyl(ray, *(t_cyl *)obj->data, &cur_t) && (cur_t > EPSILON) && (cur_t < lr_len))
            return true;
    }
    else
        return return_err(ERR_WRONG_OBJ);
    return false;
}

static bool light_ray(t_list *objs, t_ray ray, t_vec l_vec)
{
    t_list *tmp;
    t_obj *obj;

    tmp = objs;
    while (tmp)
    {
        obj = tmp->content;
        if (interrupted(ray, obj, vec_len(l_vec)))
            return false;
        tmp = tmp->next;
    }
    return true;
}

t_vec comp_color(t_scene *scene, t_hit *hit)
{
    t_vec l_vec;
    t_vec ambient;
    t_vec diffuse;
    t_vec lv_dir;

    l_vec = vec_add(hit->p, vec_scal_mul(hit->surf_n, EPSILON));
    l_vec = vec_sub(scene->light.cors, l_vec);
    lv_dir = normalize(l_vec);
    ambient = vec_mul(hit->rgb, vec_scal_mul(scene->amb.rgb, scene->amb.ratio));
    if (light_ray(scene->objs, (t_ray){.orig = hit->p, .dir = lv_dir}, l_vec))
    {
        diffuse = vec_scal_mul(hit->rgb, scene->light.brightness * fmax(0, vec_dot(hit->surf_n, lv_dir)));
        return vec_add(ambient, diffuse);
    }
    return ambient;
}
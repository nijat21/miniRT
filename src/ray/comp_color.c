#include <minirt.h>
#include <ray.h>
#include <vec.h>
#include <error_handler.h>
#include <float.h>

bool interrupted(t_ray ray, t_obj *obj, double lr_len)
{
    double cur_t;

    if (obj->type == PLANE)
        return (hit_plane(ray, *(t_plane *)obj->data, &cur_t) && (cur_t > EPSILON) && (cur_t < lr_len));
    else if (obj->type == SPHERE)
        return (hit_sphere(ray, *(t_sph *)obj->data, &cur_t) && (cur_t > EPSILON) && (cur_t < lr_len));
    else if (obj->type == CYLINDER)
        return (hit_cyl(ray, (t_cyl *)obj->data, &cur_t) && (cur_t > EPSILON) && (cur_t < lr_len));
    else
        return return_err(ERR_WRONG_OBJ);
    return false;
}

static bool light_ray(t_list *objs, t_ray ray, double len)
{
    t_list *tmp;
    t_obj *obj;

    tmp = objs;
    while (tmp)
    {
        obj = tmp->content;
        if (interrupted(ray, obj, len))
            return false;
        tmp = tmp->next;
    }
    return true;
}

t_vec comp_color(t_scene *scene, t_hit *hit)
{
    t_vec offset;
    t_vec l_vec;
    t_vec ambient;
    t_vec diffuse;
    t_vec lv_dir;
    double ndotl;

    offset = vec_add(hit->p, vec_scal_mul(hit->surf_n, (EPSILON * fmax(1.0, vec_len(hit->p)))));
    l_vec = vec_sub(scene->light.cors, offset);
    lv_dir = normalize(l_vec);
    ambient = vec_mul(hit->rgb, vec_scal_mul(scene->amb.rgb, scene->amb.ratio));
    ndotl = vec_dot(hit->surf_n, lv_dir);
    if (ndotl <= 0)
        return ambient;
    if (light_ray(scene->objs, (t_ray){.orig = offset, .dir = lv_dir}, vec_len(l_vec)))
    {
        diffuse = vec_scal_mul(hit->rgb, scene->light.brightness * fmax(0, ndotl));
        // COLOR OF LIGHT SHOULDN'T BE CONSIDERED FOR MANDATORY PART
        // diffuse = vec_mul(hit->rgb,
        //                   vec_scal_mul(scene->light.rgb, (scene->light.brightness * fmax(0, ndotl))));
        return vec_add(ambient, diffuse);
    }
    return ambient;
}
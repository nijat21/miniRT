/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:53:50 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 20:55:08 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <ray.h>
#include <vec.h>
#include <error_handler.h>
#include <float.h>

bool interrupted(t_ray ray, t_obj *obj, double lr_len)
{
    double cur_t;
    t_cyl_part part_hit;

    if (obj->type == PLANE)
        return (hit_plane(ray, *(t_plane *)obj->data, &cur_t) && (cur_t > EPSILON) && (cur_t < lr_len));
    else if (obj->type == SPHERE)
        return (hit_sphere(ray, *(t_sph *)obj->data, &cur_t) && (cur_t > EPSILON) && (cur_t < lr_len));
    else if (obj->type == CYLINDER)
        return (hit_cyl(ray, (t_cyl *)obj->data, &part_hit, &cur_t) && (cur_t > EPSILON) && (cur_t < lr_len));
    // else
    //     return return_err(ERR_WRONG_OBJ);
    return false;
}

static bool light_ray(t_list *objs, t_obj *hit_obj, t_ray ray, double len)
{
    t_list *tmp;
    t_obj *obj;

    tmp = objs;
    while (tmp)
    {
        obj = tmp->content;
        if (obj != hit_obj && interrupted(ray, obj, len))
            return false;
        tmp = tmp->next;
    }
    return true;
}

int col_clamp(double val)
{
    if (val < 0)
        return (0);
    else if (val > 255)
        return (255);
    return (val);
}

t_rgb vec_to_rgb_cl(t_vec rgb_rat)
{
    t_rgb res;

    res.r = (int)col_clamp(rgb_rat.x * 255);
    res.g = (int)col_clamp(rgb_rat.y * 255);
    res.b = (int)col_clamp(rgb_rat.z * 255);
    return res;
}

t_rgb comp_color(const t_scene *scene, const t_hit *hit)
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
        return vec_to_rgb_cl(ambient);
    if (light_ray(scene->objs, hit->obj, (t_ray){.orig = offset, .dir = lv_dir}, vec_len(l_vec)))
    {
        diffuse = vec_scal_mul(hit->rgb, scene->light.brightness * fmax(0, ndotl));
        return vec_to_rgb_cl(vec_add(ambient, diffuse));
    }
    return vec_to_rgb_cl(ambient);
}

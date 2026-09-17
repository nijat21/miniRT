#include <ray.h>
#include <vec.h>
#include <math.h>

t_vec ray_at(t_ray ray, double t)
{
    return vec_add(ray.orig, vec_scal_mul(ray.dir, t));
}

t_vport vport_init(t_disp *disp, double hfov)
{
    t_vport vport;

    vport.w = 2 * tan((hfov * M_PI / 180.0) / 2);
    vport.unit = vport.w / disp->w;
    vport.h = disp->h * vport.unit;
    return vport;
}

t_cam cam_init(t_cam cam)
{
    t_vec world;

    world = (t_vec){0, 1, 0};
    if (vec_par_norm(cam.norm, world))
        world = (t_vec){0, 0, 1};
    // cam.right = normalize(vec_cross(cam.norm, world));
    cam.right = normalize(vec_cross(world, cam.norm));
    // cam.up = normalize(vec_cross(cam.right, cam.norm));
    cam.up = normalize(vec_cross(cam.norm, cam.right));
    return cam;
}
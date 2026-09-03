#include <ray.h>
#include <vec.h>

t_vec ray_dest(t_ray ray, double t)
{
    return vec_add(ray.orig, vec_scal_mul(ray.dir, t));
}

t_vport vport_init(t_disp *disp, double hfov)
{
    t_vport vport;

    vport.w = 2 * tan(hfov / 2);
    vport.unit = vport.w / disp->w;
    vport.h = disp->h * vport.unit;
    return vport;
}

t_cam cam_init(t_cam cam)
{
    // t_cam cam = {.cors = {50.0, 0.0, 10.0},
    //              .norm = {0.0, 0.0, 1.0},
    //              .right = {},
    //              .up = {},
    //              .hfov = 70.0};
    t_vec world = (t_vec){0, 1, 0};
    if (vec_par_norm(cam.norm, world))
        world = (t_vec){0, 0, 1};
    cam.right = normalize(vec_cross(world, cam.norm));
    cam.up = normalize(vec_cross(cam.norm, cam.right));
    return cam;
}
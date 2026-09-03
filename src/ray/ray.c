#include <math.h>
#include <minirt.h>
#include <ray.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <vec.h>
#include <window.h>
#include <utils.h>

/*
    - for each pixel
    - generate a ray
    - find the closest object hit
    - compute the colour
*/

void single_ray(t_sph sph, t_ray ray)
{
    double t1;
    bool res;
    t_vec P1;

    t1 = 0;
    res = hit_sphere(ray, sph, &t1);
    if (!res)
        printf("Didn't collide\n\n");

    P1 = vec_add(ray.orig, vec_scal_mul(ray.dir, t1));
    if (res)
        printf("Collided at:\nP1 (%f, %f, %f)\n", P1.x, P1.y, P1.z);
}

// shoot rays for each pixel on viewport
int shoot_rays(t_cam cam, t_disp *disp)
{
    t_sph sph = {.cors = {50.0, 0.0, 30.0}, .rad = 10.0, .rgb = {10, 0, 255}};
    // t_cyl cyl = {.cors = {50.0, 0.0, 20.0},
    //              .norm = {0.0, 0.0, 1.0},
    //              .h = 20.0,
    //              .rad = 10.0,
    //              .rgb = {10, 0, 255}};
    t_ray ray;
    t_vport vport;
    double i;
    double j;
    double x;
    double y;
    t_vec px;

    // cam_init(cam);

    printf("-------------------------------------------------------\n");
    print_vec("foward", cam.norm);
    print_vec("right", cam.right);
    print_vec("up", cam.up);
    ray.orig = cam.cors;
    vport = vport_init(disp, cam.hfov);
    i = -1;
    while (++i < disp->h)
    {
        j = -1;
        while (++j < disp->w)
        {
            // camera is in the center and shooting through the middle of the ray
            x = (j + 0.5f) * vport.unit - (vport.w / 2);
            y = (vport.h / 2) - (i + 0.5f) * vport.unit;
            // Check by rendering images later
            t_vec right = vec_scal_mul(cam.right, x);
            t_vec up = vec_scal_mul(cam.up, y);
            px = vec_add(vec_add(cam.cors, cam.norm), vec_add(right, up));
            ray.dir = normalize(vec_sub(px, ray.orig));
            single_ray(sph, ray);
            if (j == 1)
                break;
        }
        if (i == 1)
            return 1;
    }

    return 1;
}

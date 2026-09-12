#ifndef RAY_H
#define RAY_H

#include <window.h>
#include <math.h>

typedef struct s_vport
{
    double w;
    double h;
    double unit;
} t_vport;

typedef struct s_ray
{
    t_vec orig;
    t_vec dir;
} t_ray;

typedef struct s_hit
{
    bool hit;
    double t;
    t_vec p;
    t_vec surf_n;
    t_rgb rgb;
    t_obj *obj;
} t_hit;

//---src/ray/ray.c----------------------------
bool shoot_rays(t_scene scene, t_disp *disp);

//---src/ray/intersect.c----------------------------
void dbl_swap(double *a, double *b);
bool select_t(double t0, double t1, double *t);
bool hit_sphere(t_ray ray, t_sph sph, double *t1);
bool hit_plane(t_ray ray, t_plane pl, double *t);
bool hit_cyl(t_ray ray, t_cyl cyl, double *t);

//---src/ray/hit_cyl_utils.c----------------------------
bool select_cyl_t(double ts[], t_cyl_part *labels, double *t, t_cyl_part *cap);

//---src/ray/comp_hit.c----------------------------
void comp_hit_color(t_scene *scene, t_hit *hit, t_ray ray, t_obj *obj);

//---src/ray/comp_color.c----------------------------
t_vec comp_color(t_scene *scene, t_hit *hit);

//---src/ray/ray_utils.c----------------------------
t_cam cam_init(t_cam cam);
t_vport vport_init(t_disp *disp, double hfov);
t_vec ray_at(t_ray ray, double t);

#endif // RAY_H

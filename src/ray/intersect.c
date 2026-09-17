#include <math.h>
#include <minirt.h>
#include <ray.h>
#include <vec.h>

void dbl_swap(double *a, double *b)
{
    double tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

bool select_t(double t0, double t1, double *t)
{
    if (t0 > t1)
        dbl_swap(&t0, &t1);
    if (t0 > EPSILON)
        *t = t0;
    else if (t1 > EPSILON)
        *t = t1;
    else
        return false;
    return true;
}

/*
    R(t)=Origin + t(V − Origin)
    R(t)=O+tD -> cam.cors + t * normalize(v_pixe_coors - cam.cors);

    R(t) = (40, 0, 20) + t*(0, 0, 1); -> (40, 0, 20) + (0, 0, t); -> (40, 0, 20 + t);
    |R(t)−S|^2=r^2 -> |(40, 0, 20+t) - (50, 0, 30)|^2 = 10^2; -> |vec_len(-10, 0, t - 10)|^2 = 100;

    vec_len(-10, 0, t-10) = srqt(100 + 0 + t^2 - 20t + 100) -> sqrt(t^2 - 20t + 200);
    |t^2 - 20t + 200| = 100; -> t^2 - 20t + 100 = 0; (t - 10)^2 = 0; t = 10;

    t1 = (20 + sqrt((-20)^2 - 4*1*200)) / 2*1;
    t2 = (20 - sqrt((-20)^2 - 4*1*200)) / 2*1;
*/
bool hit_sphere(t_ray ray, t_sph sph, double *t)
{
    t_vec co;
    double co_proj;
    double co_sq;
    double dist_sq;
    double rad_sq;
    double mid_to_point;
    double t0;
    double t1;

    co = vec_sub(sph.cors, ray.orig);
    co_proj = vec_dot(co, ray.dir);
    co_sq = vec_dot(co, co);
    dist_sq = co_sq - co_proj * co_proj;
    rad_sq = sph.rad * sph.rad;
    if (dist_sq > rad_sq)
        return false;
    mid_to_point = sqrt(rad_sq - dist_sq);
    t0 = co_proj - mid_to_point;
    t1 = co_proj + mid_to_point;
    return select_t(t0, t1, t);
}

/*
    A - a point in plane
    P - point ray intersects plane
    P(t) = O + tV; t>=0;

    (P - A).N = 0 -> two points in plane are perpendicular
    (O + tV - A).N = 0;
    (O - A).N + tV.N = 0;

    t = (A - O).N / V.N

    Special cases:
        1. V.N == 0 -> Vector is perpendicular to the Normal of plane
            in other words, ray is parallel to plane
        2. t < 0 -> meaning ray needs to go back to intersect with plane
*/
bool hit_plane(t_ray ray, t_plane pl, double *t)
{
    t_vec po;
    double tmp;
    double r_proj;

    r_proj = vec_dot(ray.dir, pl.norm);
    if (fabs(r_proj) < EPSILON)
        return false;
    po = vec_sub(pl.cors, ray.orig);
    tmp = vec_dot(po, pl.norm) / r_proj;
    if (tmp < EPSILON)
        return false;
    *t = tmp;
    return true;
}

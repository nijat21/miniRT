#include <stdbool.h>
#include <minirt.h>

bool select_cyl_t(double ts[], t_cyl_part *labels, double *t, t_cyl_part *cap)
{
    bool a_valid;
    bool b_valid;

    a_valid = ts[0] > EPSILON;
    b_valid = ts[1] > EPSILON;
    if (!a_valid && !b_valid)
        return (false);
    if (a_valid && (!b_valid || ts[0] < ts[1]))
    {
        *t = ts[0];
        *cap = labels[0];
    }
    else
    {
        *t = ts[1];
        *cap = labels[1];
    }
    return (true);
}
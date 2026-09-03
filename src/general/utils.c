#include <stdio.h>
#include <vec.h>

void print_vec(const char *name, t_vec v)
{
    printf("    %s: (%.17g, %.17g, %.17g)\n",
           name, v.x, v.y, v.z);
}

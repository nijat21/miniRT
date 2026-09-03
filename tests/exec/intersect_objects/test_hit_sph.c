#include <minirt.h>
#include <ray.h>
#include <vec.h>
#include <stdio.h>
#include <styles.h>
#include <math.h>
#include <utils.h>

typedef struct s_inp
{
    t_ray ray;
    t_sph sph;
} t_inp;

typedef struct s_exp
{
    bool hit;
    double t;
} t_exp;

typedef struct s_case
{
    t_inp inp;
    t_exp exp;
} t_case;

static void print_failure(int i, t_inp *inp, t_exp *exp, bool hit, double t)
{
    printf(BOLD RED "Test %2d: [FAIL]\n" RESET, i);

    printf("    expected: %s", exp->hit ? "hit" : "no hit");
    if (exp->hit)
        printf(", t=%.17g", exp->t);
    printf("\n");

    printf("    got:      %s", hit ? "hit" : "no hit");
    if (hit)
        printf(", t=%.17g", t);
    printf("\n");

    printf("\n");
    printf("    RAY\n");
    print_vec("origin", inp->ray.orig);
    print_vec("direction", inp->ray.dir);

    printf("\n");
    printf("    SPHERE\n");
    print_vec("position", inp->sph.cors);
    printf("    rad: %f\n", inp->sph.rad);

    printf("\n");
}

void test_hit_sphere(t_case cases[], int len)
{
    for (int i = 0; i < len; i++)
    {
        double t = 0.0;
        bool hit;
        bool hit_correct;
        bool t_correct;

        t_inp inp = cases[i].inp;
        t_exp exp = cases[i].exp;

        hit = hit_sphere(inp.ray, inp.sph, &t);

        hit_correct = (hit == exp.hit);
        t_correct = !exp.hit || fabs(t - exp.t) <= EPSILON * fmax(fabs(t), fmax(fabs(exp.t), 1.0));
        if (!hit_correct || !t_correct)
            print_failure(i, &inp, &exp, hit, t);
        else
            printf(BOLD GREEN "Test %2d: [PASS]\n" RESET, i);
    }
}

void test_hit_sph()
{
    t_case cases[] = {
        // 1. straight-on hit, unit direction
        {{.ray = {.orig = {0, 0, -5}, .dir = {0, 0, 1}},
          .sph = {.cors = {0, 0, 0}, .rad = 1}},
         {.hit = true, .t = 4.0}},

        // 2. tangent hit (discriminant == 0)
        {{.ray = {.orig = {0, 1, -5}, .dir = {0, 0, 1}},
          .sph = {.cors = {0, 0, 0}, .rad = 1}},
         {.hit = true, .t = 5.0}},

        // 3. clean miss (discriminant < 0)
        {{.ray = {.orig = {0, 2, -5}, .dir = {0, 0, 1}},
          .sph = {.cors = {0, 0, 0}, .rad = 1}},
         {.hit = false}},

        // 4. ray origin inside sphere -> exit point, t>0
        {{.ray = {.orig = {0, 0, 0}, .dir = {0, 0, 1}},
          .sph = {.cors = {0, 0, 0}, .rad = 2}},
         {.hit = true, .t = 2.0}},

        // 5. ray outside, pointing away -> both roots negative
        {{.ray = {.orig = {0, 0, -5}, .dir = {0, 0, -1}},
          .sph = {.cors = {0, 0, 0}, .rad = 1}},
         {.hit = false}},

        // 6. offset sphere, normalized diagonal direction
        {{.ray = {.orig = {0, 0, 0}, .dir = {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}},
          .sph = {.cors = {5, 5, 5}, .rad = 2}},
         {.hit = true, .t = 6.6602540378443855}},

        // 7. (was invalid, non-unit dir) — replaced: normalized diagonal dir, off-axis sphere
        {{.ray = {.orig = {0, 0, 0}, .dir = {0.4082482904638631, 0.4082482904638631, 0.8164965809277261}},
          .sph = {.cors = {2, 2, 4}, .rad = 1}},
         {.hit = true, .t = 3.8989794855663558}},

        // 8. on surface, inward: near root=0 rejected by EPSILON, falls back to far root
        {{.ray = {.orig = {0, 0, -1}, .dir = {0, 0, 1}},
          .sph = {.cors = {0, 0, 0}, .rad = 1}},
         {.hit = true, .t = 2.0}},

        // 9. unchanged — both roots ≤ EPSILON, genuine miss
        {{.ray = {.orig = {0, 0, -1}, .dir = {0, 0, -1}},
          .sph = {.cors = {0, 0, 0}, .rad = 1}},
         {.hit = false}},

        // 12. near root ≤ EPSILON, falls back to far root
        {{.ray = {.orig = {0, 0, -1.0000005}, .dir = {0, 0, 1}},
          .sph = {.cors = {0, 0, 0}, .rad = 1}},
         {.hit = true, .t = 2.0000005}},
    };
    test_hit_sphere(cases, sizeof(cases) / sizeof(cases[0]));
}
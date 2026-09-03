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
    t_plane pl;
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
    printf("    PLANE\n");
    print_vec("position", inp->pl.cors);
    print_vec("normal", inp->pl.norm);

    printf("\n");
}

void test_hit_plane(t_case *cases, int len)
{
    for (int i = 0; i < len; i++)
    {
        double t = 0.0;
        bool hit;
        bool hit_correct;
        bool t_correct;

        t_inp inp = cases[i].inp;
        t_exp exp = cases[i].exp;

        hit = hit_plane(inp.ray, inp.pl, &t);

        hit_correct = (hit == exp.hit);
        t_correct = !exp.hit || fabs(t - exp.t) <= EPSILON * fmax(fabs(t), fmax(fabs(exp.t), 1.0));

        if (!hit_correct || !t_correct)
            print_failure(i, &inp, &exp, hit, t);
        else
            printf(BOLD GREEN "Test %2d: [PASS]\n" RESET, i);
    }
}

void test_hit_pl()
{
    t_case cases[] = {
        /* =========================================================
         * Plane 1: x = 0
         * A    = (0, 0, 0)
         * Norm = (1, 0, 0)
         * ========================================================= */

        /* perpendicular -> hit, t = 1 */
        {.inp = {.ray = {{1, 2, 3}, {-1, 0, 0}}, .pl = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}}}, .exp = {true, 1.0}},

        /* angled -> hit, normalized dir -> t = sqrt(2) */
        {.inp = {.ray = {{1, 2, 3}, {-0.7071067811865476, -0.7071067811865476, 0}}, .pl = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}}}, .exp = {true, 1.4142135623730951}},

        /* parallel -> miss */
        {.inp = {.ray = {{1, 2, 3}, {0, 1, 0}}, .pl = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}}}, .exp = {false, 0.0}},

        /* pointing away -> negative t -> miss */
        {.inp = {.ray = {{1, 2, 3}, {1, 0, 0}}, .pl = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}}}, .exp = {false, -1.0}},

        /* origin on plane -> boundary -> hit at t = 0 */
        {.inp = {.ray = {{0, 2, 3}, {1, 0, 0}}, .pl = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}}}, .exp = {true, 0.0}},

        /* from behind -> hit, origin is opposite normal side */
        {.inp = {.ray = {{-1, 2, 3}, {1, 0, 0}}, .pl = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}}}, .exp = {true, 1.0}},

        /* below EPSILON -> treated as parallel -> miss */
        {.inp = {.ray = {{1, 2, 3}, {-1e-12, 1.0, 0}}, .pl = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}}}, .exp = {false, 0.0}},

        /* just above EPSILON -> hit, t = 100000 */
        {.inp = {.ray = {{1, 2, 3}, {-1e-5, 1.0, 0}}, .pl = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}}}, .exp = {true, 100000.0}},

        /* =========================================================
         * Plane 2: y = 2
         * A    = (0, 2, 0)
         * Norm = (0, 1, 0)
         * ========================================================= */

        /* perpendicular -> hit, t = 2 */
        {.inp = {.ray = {{1, 0, 3}, {0, 1, 0}}, .pl = {{0, 2, 0}, {0, 1, 0}, {0, 0, 0}}}, .exp = {true, 2.0}},

        /* angled -> hit, normalized dir -> t = 2 * sqrt(2) */
        {.inp = {.ray = {{1, 0, 3}, {0.7071067811865476, 0.7071067811865476, 0}}, .pl = {{0, 2, 0}, {0, 1, 0}, {0, 0, 0}}}, .exp = {true, 2.8284271247461903}},

        /* parallel -> miss */
        {.inp = {.ray = {{1, 0, 3}, {1, 0, 0}}, .pl = {{0, 2, 0}, {0, 1, 0}, {0, 0, 0}}}, .exp = {false, 0.0}},

        /* pointing away -> negative t -> miss */
        {.inp = {.ray = {{1, 0, 3}, {0, -1, 0}}, .pl = {{0, 2, 0}, {0, 1, 0}, {0, 0, 0}}}, .exp = {false, -2.0}},

        /* origin on plane -> boundary -> hit at t = 0 */
        {.inp = {.ray = {{1, 2, 3}, {0, 1, 0}}, .pl = {{0, 2, 0}, {0, 1, 0}, {0, 0, 0}}}, .exp = {true, 0.0}},

        /* from behind -> hit, origin is opposite normal side */
        {.inp = {.ray = {{1, 1, 3}, {0, 1, 0}}, .pl = {{0, 2, 0}, {0, 1, 0}, {0, 0, 0}}}, .exp = {true, 1.0}},

        /* below EPSILON -> treated as parallel -> miss */
        {.inp = {.ray = {{1, 0, 3}, {1.0, 1e-12, 0}}, .pl = {{0, 2, 0}, {0, 1, 0}, {0, 0, 0}}}, .exp = {false, 0.0}},

        /* just above EPSILON -> hit, t = 200000 */
        {.inp = {.ray = {{1, 0, 3}, {1.0, 1e-5, 0}}, .pl = {{0, 2, 0}, {0, 1, 0}, {0, 0, 0}}}, .exp = {true, 200000.0}},

        /* =========================================================
         * Plane 3: z = -1
         * A    = (0, 0, -1)
         * Norm = (0, 0, 1)
         * ========================================================= */

        /* perpendicular -> hit, t = 4 */
        {.inp = {.ray = {{1, 2, 3}, {0, 0, -1}}, .pl = {{0, 0, -1}, {0, 0, 1}, {0, 0, 0}}}, .exp = {true, 4.0}},

        /* angled -> hit, normalized dir -> t = 4 * sqrt(2) */
        {.inp = {.ray = {{1, 2, 3}, {0.7071067811865476, 0, -0.7071067811865476}}, .pl = {{0, 0, -1}, {0, 0, 1}, {0, 0, 0}}}, .exp = {true, 5.656854249492381}},

        /* parallel -> miss */
        {.inp = {.ray = {{1, 2, 3}, {1, 0, 0}}, .pl = {{0, 0, -1}, {0, 0, 1}, {0, 0, 0}}}, .exp = {false, 0.0}},

        /* pointing away -> negative t -> miss */
        {.inp = {.ray = {{1, 2, 3}, {0, 0, 1}}, .pl = {{0, 0, -1}, {0, 0, 1}, {0, 0, 0}}}, .exp = {false, -4.0}},

        /* origin on plane -> boundary -> hit at t = 0 */
        {.inp = {.ray = {{1, 2, -1}, {0, 0, 1}}, .pl = {{0, 0, -1}, {0, 0, 1}, {0, 0, 0}}}, .exp = {true, 0.0}},

        /* from behind -> hit, origin is opposite normal side */
        {.inp = {.ray = {{1, 2, -2}, {0, 0, 1}}, .pl = {{0, 0, -1}, {0, 0, 1}, {0, 0, 0}}}, .exp = {true, 1.0}},

        /* below EPSILON -> treated as parallel -> miss */
        {.inp = {.ray = {{1, 2, 3}, {1.0, 0, -1e-12}}, .pl = {{0, 0, -1}, {0, 0, 1}, {0, 0, 0}}}, .exp = {false, 0.0}},

        /* just above EPSILON -> hit, t = 400000 */
        {.inp = {.ray = {{1, 2, 3}, {1.0, 0, -1e-5}}, .pl = {{0, 0, -1}, {0, 0, 1}, {0, 0, 0}}}, .exp = {true, 400000.0}},

        /* =========================================================
         * Plane 4: x + y + z = 6
         * A    = (1, 2, 3)
         * Norm = (1/sqrt(3), 1/sqrt(3), 1/sqrt(3))
         * ========================================================= */

        /* perpendicular -> hit, t = 2 * sqrt(3) */
        {.inp = {.ray = {{0, 0, 0}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}}, .pl = {{1, 2, 3}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}, {0, 0, 0}}}, .exp = {true, 3.4641016151377544}},

        /* angled -> hit, normalized dir -> t = 2 * sqrt(5) */
        {.inp = {.ray = {{0, 0, 0}, {0.8944271909999159, 0.4472135954999579, 0}}, .pl = {{1, 2, 3}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}, {0, 0, 0}}}, .exp = {true, 4.47213595499958}},

        /* parallel -> miss */
        {.inp = {.ray = {{0, 0, 0}, {0.7071067811865476, -0.7071067811865476, 0}}, .pl = {{1, 2, 3}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}, {0, 0, 0}}}, .exp = {false, 0.0}},

        /* pointing away -> negative t -> miss */
        {.inp = {.ray = {{0, 0, 0}, {-0.5773502691896258, -0.5773502691896258, -0.5773502691896258}}, .pl = {{1, 2, 3}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}, {0, 0, 0}}}, .exp = {false, -3.4641016151377544}},

        /* origin on plane -> boundary -> hit at t = 0 */
        {.inp = {.ray = {{1, 2, 3}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}}, .pl = {{1, 2, 3}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}, {0, 0, 0}}}, .exp = {true, 0.0}},

        /* from behind -> hit */
        {.inp = {.ray = {{0, 0, 0}, {0.8944271909999159, 0.4472135954999579, 0}}, .pl = {{1, 2, 3}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}, {0, 0, 0}}}, .exp = {true, 4.47213595499958}},

        /*
         * below EPSILON -> treated as parallel -> miss
         *
         * dot(D, N) ≈ 4.08e-13
         */
        {.inp = {.ray = {{0, 0, 0}, {0.7071067811861931, -0.7071067811861931, 7.071067811863e-13}}, .pl = {{1, 2, 3}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}, {0, 0, 0}}}, .exp = {false, 0.0}},

        /*
         * above EPSILON -> hit, t = 3e6
         *
         * dot(D, N) = 2e-6 / sqrt(3)
         * numerator = 6 / sqrt(3)
         * t = 3e6
         */
        {.inp = {.ray = {{0, 0, 0}, {0.7071067811865476, -0.7071067811865476, 2e-6}}, .pl = {{1, 2, 3}, {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}, {0, 0, 0}}}, .exp = {true, 3e6}}};
    test_hit_plane(cases, sizeof(cases) / sizeof(cases[0]));
}
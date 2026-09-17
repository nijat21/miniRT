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
  t_cyl cyl;
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
  printf("    CYLINDER\n");
  print_vec("position", inp->cyl.cors);
  print_vec("normal", inp->cyl.norm);
  printf("h:   %.17g\n", inp->cyl.h);
  printf("rad: %.17g\n", inp->cyl.rad);

  printf("\n");
}

void test_hit_cylinder(t_case cases[], int len)
{
  for (int i = 0; i < len; i++)
  {
    double t = 0.0;
    bool hit;
    bool hit_correct;
    bool t_correct;

    t_inp inp = cases[i].inp;
    t_exp exp = cases[i].exp;

    hit = hit_cyl(inp.ray, &inp.cyl, &t);

    hit_correct = (hit == exp.hit);
    t_correct = !exp.hit || fabs(t - exp.t) <= EPSILON * fmax(fabs(t), fmax(fabs(exp.t), 1.0));

    if (!hit_correct || !t_correct)
      print_failure(i, &inp, &exp, hit, t);
    else
      printf(BOLD GREEN "Test %2d: [PASS]\n" RESET, i);
  }
}

void test_hit_cyl()
{
  t_case cases[] = {
      // 0. perpendicular hit on side, within height range
      {{.ray = {.orig = {-5, 0, 2}, .dir = {1, 0, 0}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 4.0}},

      // 1. straight down axis, hits bottom cap at z=-h/2=-2.5
      {{.ray = {.orig = {0, 0, -5}, .dir = {0, 0, 1}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 2.5}},

      // 2. straight up into top cap at z=+h/2=2.5
      {{.ray = {.orig = {0, 0, 10}, .dir = {0, 0, -1}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 7.5}},

      // 3. parallel to axis, outside radius -> total miss
      {{.ray = {.orig = {2, 0, -5}, .dir = {0, 0, 1}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = false}},

      // 4. oblique side hit, starting at mid-height so it stays in range
      {{.ray = {.orig = {-5, 0, 0}, .dir = {0.9578262852211514, 0, 0.2873478855663454}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 4.176122603564222}},

      // 5. perpendicular ray, offset beyond radius -> miss
      {{.ray = {.orig = {-5, 3, 2}, .dir = {1, 0, 0}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = false}},

      // 6. origin inside cylinder, exits through side
      {{.ray = {.orig = {0, 0, 2}, .dir = {1, 0, 0}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 1.0}},

      // 7. origin inside, exits top cap at z=2.5 -> t=0.5
      {{.ray = {.orig = {0, 0, 2}, .dir = {0, 0, 1}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 0.5}},

      // 8. crosses infinite side but above finite height -> miss
      {{.ray = {.orig = {-5, 0, 8}, .dir = {1, 0, 0}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = false}},

      // 9. hits bottom cap near its edge, z=-2.5 -> t=2.5
      {{.ray = {.orig = {0.9, 0, -5}, .dir = {0, 0, 1}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 2.5}},

      // 10. tilted axis (1,1,1) normalized, ray straight into side perpendicular to axis
      {{.ray = {.orig = {3.5355339059327378, -3.5355339059327378, 0}, .dir = {-0.7071067811865476, 0.7071067811865476, 0}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0.5773502691896258, 0.5773502691896258, 0.5773502691896258}, .h = 6, .rad = 1}},
       {.hit = true, .t = 4.0}},

      // 11. tangent to side (discriminant == 0)
      {{.ray = {.orig = {-5, 1, 0}, .dir = {1, 0, 0}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 5.0}},

      // 12. oblique ray misses cap plane by radius -> total miss
      {{.ray = {.orig = {3, 0, -10}, .dir = {0.09950371902099892, 0, 0.9950371902099892}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = false}},

      // 13. hits top cap near its edge, z=2.5 -> t=7.5
      {{.ray = {.orig = {0.9, 0, 10}, .dir = {0, 0, -1}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 7.5}},

      // 14. rim seam: side hit exactly at height boundary z=h/2
      {{.ray = {.orig = {-5, 0, 2.5}, .dir = {1, 0, 0}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 4.0}},

      // 15. EPSILON fallback: ray starts exactly on side, heading inward -> near root rejected, falls to far root
      {{.ray = {.orig = {-1, 0, 0}, .dir = {1, 0, 0}},
        .cyl = {.cors = {0, 0, 0}, .norm = {0, 0, 1}, .h = 5, .rad = 1}},
       {.hit = true, .t = 2.0}},

      // 16. large-coordinate precision (cylinder offset far from origin)
      {{.ray = {.orig = {0, 0, 0}, .dir = {1, 0, 0}},
        .cyl = {.cors = {3000000, 0, 0}, .norm = {0, 0, 1}, .h = 10, .rad = 1}},
       {.hit = true, .t = 2999999.0}},
  };
  test_hit_cylinder(cases, sizeof(cases) / sizeof(cases[0]));
}
#include <stdio.h>
#include <styles.h>

void test_hit_pl();
void test_hit_sph();
void test_hit_cyl();

int main()
{
    printf(INFO "TEST - RAY PLANE INTERSECTION\n" RESET);
    printf("---------------------------------------------------\n");
    test_hit_pl();
    printf("\n");

    printf(INFO "TEST - RAY SPHERE INTERSECTION\n" RESET);
    printf("---------------------------------------------------\n");
    test_hit_sph();
    printf("\n");

    printf(INFO "TEST - RAY CYLINDER INTERSECTION\n" RESET);
    printf("---------------------------------------------------\n");
    test_hit_cyl();
    printf("\n");

    return 0;
}
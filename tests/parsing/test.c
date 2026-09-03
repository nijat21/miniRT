#include <minirt.h>
#include "../../src/Libft/libft.h"

static void print_scene(t_scene *scene);
static void print_camera(t_cam cam);
static void print_ambient(t_amb amb);
static void print_light(t_light light);

int main(int argc, char **argv)
{
    t_scene scene = {0};

    if (argc != 2)
        return (printf("Error\nUsage: ./miniRT file.rt\n"), 1);
    if (!parse_scene(argv[1], &scene))
        return (printf("Error\nParsing failed\n"), 1);
    print_scene(&scene);
    return (0);
}

void print_scene(t_scene *scene)
{
    t_list *current;
    t_object *obj;

    printf("\n====== SCENE CONTENT ======\n\n");

    print_ambient(scene->amb);
    print_camera(scene->cam);
    print_light(scene->light);

    printf("\n------ OBJECTS -------\n\n");

    current = scene->objects;
    while (current)
    {
        obj = (t_object *)current->content;
        if (obj->type == SPHERE)
        {
            t_sph *sp = (t_sph *)obj->data;
            printf("SPHERE:\n");
            printf(" center: (%f, %f, %f)\n", sp->cors.x, sp->cors.y, sp->cors.z);
            printf(" radius: %f\n", sp->rad);
            printf(" color: (%f, %f, %f)\n", sp->rgb.r, sp->rgb.g, sp->rgb.b);
            printf("\n");
        }
        else if (obj->type == CYLINDER)
        {
            t_cyl *cy = (t_cyl *)obj->data;
            printf("CYLINDER:\n");
            printf(" center: (%f, %f, %f)\n", cy->cors.x, cy->cors.y, cy->cors.z);
            printf(" normalized orientation vector: (%f, %f, %f)\n", cy->norm.x, cy->norm.y, cy->norm.z);
            printf(" diameter: %f\n", cy->rad * 2);
            printf(" height: %f\n", cy->h);
            printf(" color: (%f, %f, %f)\n", cy->rgb.r, cy->rgb.g, cy->rgb.b);
            printf("\n");
        }
        else if (obj->type == PLANE)
        {
            t_plane *pl = (t_plane *)obj->data;
            printf("PLANE:\n");
            printf(" point coordinates: (%f, %f, %f)\n", pl->cors.x, pl->cors.y, pl->cors.z);
            printf(" normalized orientation vector: (%f, %f, %f)\n", pl->norm.x, pl->norm.y, pl->norm.z);
            printf(" color: (%f, %f, %f)\n", pl->rgb.r, pl->rgb.g, pl->rgb.b);
            printf("\n");
        }
        else if (obj->type == SQUARE)
        {
            t_square *sq = (t_square *)obj->data;
            printf("SQUARE:\n");
            printf(" center: (%f, %f, %f)\n", sq->cors.x, sq->cors.y, sq->cors.z);
            printf(" normalized orientation vector: (%f, %f, %f)\n", sq->norm.x, sq->norm.y, sq->norm.z);
            printf(" side size: %f\n", sq->side_len);
            printf(" color: (%f, %f, %f)\n", sq->rgb.r, sq->rgb.g, sq->rgb.b);
            printf("\n");
        }
        current = current->next;
    }
}

static void print_camera(t_cam cam)
{
    double len;

    printf("CAMERA:\n");
    printf(" position: (%f, %f, %f)\n", cam.cors.x, cam.cors.y, cam.cors.z);
    printf(" direction: (%f, %f, %f)\n", cam.norm.x, cam.norm.y, cam.norm.z);
    printf(" FOV: %f\n", cam.hfov);

    // check normalization
    len = sqrt(pow(cam.norm.x, 2) + pow(cam.norm.y, 2) + pow(cam.norm.z, 2));
    if (fabs(len - 1.0) > 1e-6)
        printf("WARNING: camera direction not normalized (len=%f)\n", len);
    if (cam.hfov < 0 || cam.hfov > 180)
        printf("ERROR: invalid FOV\n");
    printf("\n");
}

static void print_ambient(t_amb amb)
{
    printf("AMBIENT:\n");
    printf(" ratio: %f\n", amb.ratio);
    printf(" color: (%f, %f, %f)\n", amb.rgb.r, amb.rgb.g, amb.rgb.b);
    if (amb.ratio < 0 || amb.ratio > 1)
        printf("ERROR: invalid ambient ratio\n");
    printf("\n");
}

static void print_light(t_light light)
{
    printf("LIGHT:\n");
    printf(" position: (%f, %f, %f)\n", light.cors.x, light.cors.y, light.cors.z);
    printf(" brightness: %f\n", light.brightness);
    printf(" color: (%f, %f, %f)\n", light.rgb.r, light.rgb.g, light.rgb.b);
    if (light.brightness < 0 || light.brightness > 1)
        printf("ERROR: invalid light brightness\n");
    printf("\n");
}

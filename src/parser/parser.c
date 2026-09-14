#include <minirt.h>
#include <parser.h>
#include <utils.h>
// reads file

void parse_line(char *line, t_scene *scene)
{
    char **tokens;

    tokens = ft_split_spaces(line);
    if (!tokens || !tokens[0])
    {
        if (tokens)
            free_split(tokens, count_tokens(tokens));
        return;
    }
    if (!ft_strncmp(tokens[0], "R", 1))
        parse_resolution(tokens, scene);
    else if (!ft_strncmp(tokens[0], "A", 1))
        parse_ambient(tokens, scene);
    else if (!ft_strncmp(tokens[0], "C", 1))
        parse_camera(tokens, scene);
    else if (!ft_strncmp(tokens[0], "L", 1))
        parse_light(tokens, scene);
    else if (!ft_strncmp(tokens[0], "sp", 2))
        parse_sphere(tokens, scene);
    else if (!ft_strncmp(tokens[0], "pl", 2))
        parse_plane(tokens, scene);
    else if (!ft_strncmp(tokens[0], "sq", 2))
        parse_square(tokens, scene);
    else if (!ft_strncmp(tokens[0], "cy", 2))
        parse_cylinder(tokens, scene);
    // else if (!ft_strncmp(tokens[0], "tr", 2))
    //     parse_triangle(tokens, scene);
    else
        error("Unknown identifier");
    free_split(tokens, count_tokens(tokens));
}
void print_scene(t_scene *scene)
{
    t_list *current;
    t_obj *obj;
    t_sph *sp;
    t_plane *pl;
    t_cyl *cyl;

    printf("\n");
    printf("========== PARSED SCENE ==========\n");

    printf("\n[RESOLUTION]\n");
    printf("has_res : %d\n", scene->has_res);
    printf("width   : %d\n", scene->w);
    printf("height  : %d\n", scene->h);

    printf("\n[AMBIENT]\n");
    printf("has_amb : %d\n", scene->has_amb);
    if (scene->has_amb)
    {
        printf("ratio : %.6f\n", scene->amb.ratio);
        printf("color : %.6f,%.6f,%.6f\n",
               scene->amb.rgb.x,
               scene->amb.rgb.y,
               scene->amb.rgb.z);
    }

    printf("\n[CAMERA]\n");
    printf("has_cam : %d\n", scene->has_cam);
    if (scene->has_cam)
    {
        print_vec("position", scene->cam.cors);
        printf("\n");
        print_vec("orientation", scene->cam.norm);
        printf("\n");
        printf("fov: %.6f\n", scene->cam.hfov);
    }

    printf("\n[LIGHT]\n");
    printf("has_light : %d\n", scene->has_light);
    if (scene->has_light)
    {
        print_vec("position", scene->light.cors);
        printf("\n");
        printf("brightness: %.6f\n", scene->light.brightness);
        printf("color : %.6f,%.6f,%.6f\n",
               scene->light.rgb.x,
               scene->light.rgb.y,
               scene->light.rgb.z);
    }

    printf("\n[OBJECTS]\n");

    current = scene->objs;
    while (current)
    {
        obj = (t_obj *)current->content;

        printf("\nobject type: %d\n", obj->type);

        if (obj->type == SPHERE)
        {
            sp = (t_sph *)obj->data;

            print_vec("position", sp->cors);
            printf("\n");

            printf("radius   : %.6f\n", sp->rad);
            printf("color    : %.6f,%.6f,%.6f\n",
                   sp->rgb.x,
                   sp->rgb.y,
                   sp->rgb.z);
        }
        else if (obj->type == PLANE)
        {
            pl = (t_plane *)obj->data;

            print_vec("position", pl->cors);
            printf("\n");

            print_vec("normal", pl->norm);
            printf("\n");

            printf("color    : %.6f,%.6f,%.6f\n",
                   pl->rgb.x,
                   pl->rgb.y,
                   pl->rgb.z);
        }
        else if (obj->type == CYLINDER)
        {
            cyl = (t_cyl *)obj->data;

            print_vec("position", cyl->cors);
            printf("\n");

            print_vec("normal", cyl->norm);
            printf("\n");

            printf("diameter : %.6f\n", cyl->rad * 2.0);
            printf("height   : %.6f\n", cyl->h);

            printf("color    : %.6f,%.6f,%.6f\n",
                   cyl->rgb.x,
                   cyl->rgb.y,
                   cyl->rgb.z);
        }

        current = current->next;
    }

    printf("\n==================================\n\n");
}

void scene_init(t_scene *scene)
{
    scene->objs = NULL;
    scene->has_res = false;
    scene->has_amb = false;
    scene->has_cam = false;
    scene->has_light = false;
}

int parse_scene(char *filename, t_scene *scene)
{
    int fd;
    char *line;

    scene_init(scene);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error("Failed to open file");
    while ((line = get_next_line(fd)))
    {
        parse_line(line, scene);
        free(line);
    }
    close(fd);
    print_scene(scene);
    return (1);
}

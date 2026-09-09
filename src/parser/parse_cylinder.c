#include <minirt.h>
#include <parser.h>
#include <libft.h>
/*

cy  50.0,0.0,20.6 0,0,1.0   14.2 21.42  10,0,255

tokens[1] center of base of cylinder // better to use middle of cylinder!!!
tokens[2] normal vector
tokens[3] cylinder diameter
tokens[4] cylinder height
tokens[5] color

*/

void parse_cylinder(char **tokens, t_scene *scene)
{
    t_object *obj;
    t_cyl *cy;
    t_list *node;

    if (count_tokens(tokens) != 6)
        error("Invalid cylinder format");
    cy = malloc(sizeof(t_cyl));
    obj = malloc(sizeof(t_object));
    if (!cy || !obj)
    {
        free(cy);
        free(obj);
        error("Malloc failed");
    }
    cy->cors = parse_vec(tokens[1]);
    cy->norm = parse_vec(tokens[2]);
    if (vec_len(cy->norm) == 0)
        error("Cylinder norm cannot be zero");
    cy->norm = normalize(cy->norm);
    cy->rad = parse_double(tokens[3]) / 2.0;
    cy->h = parse_double(tokens[4]);
    if (cy->rad <= 0 || cy->h <= 0)
        error("Cylinder diameter and height must be > 0");
    cy->half_h = cy->h / 2.0;
    cy->rgb = parse_color(tokens[5]);
    obj->type = CYLINDER;
    obj->data = cy;
    node = ft_lstnew(obj);
    if (!node)
    {
        free(cy);
        free(obj);
        error("Malloc failed");
    }
    ft_lstadd_back(&scene->objects, node);
}

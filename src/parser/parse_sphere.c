#include <minirt.h>
#include <parser.h>
#include <libft.h>

void parse_sphere(char **tokens, t_scene *scene)
{
    t_obj *obj;
    t_sph *sp;
    t_list *node;

    if (count_tokens(tokens) != 4)
        error("Invalid sphere format");
    sp = malloc(sizeof(t_sph));
    obj = malloc(sizeof(t_obj));
    if (!sp || !obj)
        error("Malloc failed");
    sp->cors = parse_vec(tokens[1]);
    sp->rad = parse_double(tokens[2]) / 2.0;
    if (sp->rad <= 0)
        error("Sphere radius must be > 0");
    sp->rgb = parse_color(tokens[3]);
    obj->type = SPHERE;
    obj->data = sp;
    node = ft_lstnew(obj);
    if (!node)
        error("Malloc failed");
    ft_lstadd_back(&scene->objs, node);
}

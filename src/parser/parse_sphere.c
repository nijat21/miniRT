#include <minirt.h>
#include <parser.h>
#include <libft.h>

void	parse_sphere(char **tokens, t_scene *scene)
{
	t_obj	*obj;
	t_sph	*sp;
	t_list	*node;

	if (count_tokens(tokens) != 4)
		error(scene, "Invalid sphere format");
	sp = malloc(sizeof(t_sph));
	obj = malloc(sizeof(t_obj));
	if (!sp || !obj)
		error(scene, "Malloc failed");
	sp->cors = parse_vec(tokens[1], scene);
	sp->rad = parse_double(tokens[2], scene) / 2.0;
	if (sp->rad <= 0)
		error(scene, "Sphere radius must be > 0");
	sp->rgb = parse_color(tokens[3], scene);
	obj->type = SPHERE;
	obj->data = sp;
	node = ft_lstnew(obj);
	if (!node)
		error(scene, "Malloc failed");
	ft_lstadd_back(&scene->objs, node);
}

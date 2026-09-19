#include <minirt.h>
#include <parser.h>
#include <libft.h>

static t_sph	*init_sph(char **tokens, t_scene *scene)
{
	t_sph	*sp;

	sp = malloc(sizeof(t_sph));
	if (!sp)
		error(scene, "Malloc failed");
	sp->cors = parse_vec(tokens[1], scene);
	sp->rad = parse_double(tokens[2], scene);
	if (sp->rad <= 0)
	{
		free(sp);
		error(scene, "Sphere diameter must be > 0");
	}
	sp->rgb = parse_color(tokens[3], scene);
	return (sp);
}

static t_obj	*create_sph(t_sph *sp, t_scene *scene)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
	{
		free(sp);
		error(scene, "Malloc failed");
	}
	obj->type = SPHERE;
	obj->data = sp;
	return (obj);
}

void	parse_sphere(char **tokens, t_scene *scene)
{
	t_obj	*obj;
	t_sph	*sp;
	t_list	*node;

	if (count_tokens(tokens) != 4)
		error(scene, "Invalid sphere format");
	sp = init_sph(tokens, scene);
	add_obj(scene, SPHERE, sp);
}

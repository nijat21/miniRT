#include <minirt.h>
#include <parser.h>
#include <libft.h>
/*

pl 0,0,0 0,1,0 255,255,255

tokens[1] point on plane
tokens[2] normal vector
tokens[3] color

*/

void	parse_plane(char **tokens, t_scene *scene)
{
	t_obj	*obj;
	t_plane	*pl;
	t_list	*node;

	if (count_tokens(tokens) != 4)
		error("Invalid plane format");
	pl = malloc(sizeof(t_plane));
	obj = malloc(sizeof(t_obj));
	if (!pl || !obj)
		error("Malloc failed");
	pl->cors = parse_vec(tokens[1]);
	pl->norm = parse_vec(tokens[2]);
	if (vec_len(pl->norm) == 0)
		error("Plane norm cannot be zero");
	pl->norm = normalize(pl->norm);
	pl->rgb = parse_color(tokens[3]);
	obj->type = PLANE;
	obj->data = pl;
	node = ft_lstnew(obj);
	if (!node)
		error("Malloc failed");
	ft_lstadd_back(&scene->objs, node);
}

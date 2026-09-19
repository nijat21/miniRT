#include <minirt.h>
#include <parser.h>
#include <libft.h>
/*

pl 0,0,0 0,1,0 255,255,255

tokens[1] point on plane
tokens[2] normal vector
tokens[3] color

*/

static t_plane	*init_plane(char **tokens, t_scene *scene)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		error(scene, "Malloc failed");
	pl->cors = parse_vec(tokens[1], scene);
	pl->norm = parse_vec(tokens[2], scene);
	if (vec_len(pl->norm) == 0)
	{
		free(pl);
		error(scene, "Plane norm cannot be zero");
	}
	pl->norm = normalize(pl->norm);
	pl->rgb = parse_color(tokens[3], scene);
	return (pl);
}

void	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*pl;

	if (count_tokens(tokens) != 4)
		error(scene, "Invalid plane format");
	pl = init_plane(tokens, scene);
	add_obj(scene, PLANE, pl);
}

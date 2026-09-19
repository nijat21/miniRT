#include <minirt.h>
#include <parser.h>
#include <libft.h>
/*

pl 0,0,0 0,1,0 255,255,255

tokens[1] point on plane
tokens[2] normal vector
tokens[3] color

*/

static void	check_plane_norm(t_vec norm, t_scene *scene)
{
	if (norm.x < -1.0 || norm.x > 1.0
		|| norm.y < -1.0 || norm.y > 1.0
		|| norm.z < -1.0 || norm.z > 1.0)
		error(scene, "Plane orientation must be in range [-1,1]");
	if (vec_len(norm) == 0.0)
		error(scene, "Plane norm cannot be zero");
}

static t_plane	*init_plane(char **tokens, t_scene *scene)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		error(scene, "Malloc failed");
	pl->cors = parse_vec(tokens[1], scene);
	pl->norm = parse_vec(tokens[2], scene);
	check_plane_norm(pl->norm, scene);
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

#include <minirt.h>
#include <parser.h>

/*
C 0,0,0 0,0,0 120
*/
void	parse_camera(char **tokens, t_scene *scene)
{
	t_cam	cam;

	if (scene->has_cam)
		error("Camera already defined");
	if (count_tokens(tokens) != 4)
		error("Invalid camera format");
	cam.cors = parse_vec(tokens[1]);
	cam.norm = parse_vec(tokens[2]);
	if (cam.norm.x < -1.0 || cam.norm.x > 1.0
		|| cam.norm.y < -1.0 || cam.norm.y > 1.0
		|| cam.norm.z < -1.0 || cam.norm.z > 1.0)
		error("Camera orientation must be in range [-1,1]");
	if (vec_len(cam.norm) == 0.0)
		error("Camera orientation cannot be zero");
	cam.norm = normalize(cam.norm);
	cam.hfov = ft_atoi(tokens[3]);
	if (cam.hfov < 0 || cam.hfov > 180)
		error("Invalid FOV range");
	scene->cam = cam;
	scene->has_cam = true;
}

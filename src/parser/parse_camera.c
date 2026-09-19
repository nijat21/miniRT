#include <minirt.h>
#include <parser.h>

/*
C 0,0,0 0,0,0 120
*/
void	parse_camera(char **tokens, t_scene *scene)
{
	t_cam	cam;

	if (scene->has_cam)
		error(scene, "Camera already defined");
	if (count_tokens(tokens) != 4)
		error(scene, "Invalid camera format");
	cam.cors = parse_vec(tokens[1], scene);
	cam.norm = parse_vec(tokens[2], scene);
	if (cam.norm.x < -1.0 || cam.norm.x > 1.0
		|| cam.norm.y < -1.0 || cam.norm.y > 1.0
		|| cam.norm.z < -1.0 || cam.norm.z > 1.0)
		error(scene, "Camera orientation must be in range [-1,1]");
	if (vec_len(cam.norm) == 0.0)
		error(scene, "Camera orientation cannot be zero");
	cam.norm = normalize(cam.norm);
	cam.hfov = ft_atoi(tokens[3]);
	if (cam.hfov < 0 || cam.hfov > 180)
		error(scene, "Invalid FOV range");
	scene->cam = cam;
	scene->has_cam = true;
}

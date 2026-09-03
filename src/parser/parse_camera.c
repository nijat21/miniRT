#include <minirt.h>
#include <parser.h>

/*
C 0,0,0 0,0,0 120
*/
void parse_camera(char **tokens, t_scene *scene)
{
    t_cam cam;

    if (scene->has_cam)
        error("Camera already defined");
    if (count_tokens(tokens) != 4)
        error("Invalid camera format");

    // position
    cam.cors = parse_vec(tokens[1]);

    // orientation
    cam.norm = parse_vec(tokens[2]);
    if (cam.norm.x < -1 || cam.norm.x > 1 || cam.norm.y < -1 || cam.norm.y > 1 || cam.norm.z < -1 || cam.norm.z > 1)
        error("Camera orientation must be in range [-1,1]");

    // normalize vectpr
    cam.norm = normalize(cam.norm);

    // FOV
    cam.hfov = ft_atoi(tokens[3]);
    if (cam.hfov < 0 || cam.hfov > 180)
        error("Invalid FOV range");
    scene->cam = cam;
    scene->has_cam = true;
}

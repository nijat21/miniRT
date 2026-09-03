#include <minirt.h>
#include <parser.h>
/*

A 0.2 255,255,255

Tokens:
[0] = "A"
[1] = ratio (double)
[2] = color

*/

void parse_ambient(char **tokens, t_scene *scene)
{
    if (scene->has_amb)
        error("Ambient already defined");
    if (count_tokens(tokens) != 3)
        error("Invalid ambient format");
    scene->amb.ratio = ft_atof(tokens[1]);
    if (scene->amb.ratio < 0.0 || scene->amb.ratio > 1.0)
        error("Ambient ratio must be in range [0.0,1.0]");
    scene->amb.rgb = parse_color(tokens[2]);
    scene->has_amb = true;
}

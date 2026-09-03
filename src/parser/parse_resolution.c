#include <minirt.h>
#include <parser.h>

void parse_resolution(char **tokens, t_scene *scene)
{
    if (scene->has_res)
        error("Resolution already defined");
    if (count_tokens(tokens) != 3)
        error("Invalid resolution format");

    scene->w = ft_atoi(tokens[1]);
    scene->h = ft_atoi(tokens[2]);

    if (scene->w <= 0 || scene->h <= 0)
        error("Invalid resolution values");
    scene->has_res = true;
}

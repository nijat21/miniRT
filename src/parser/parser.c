#include <minirt.h>
#include <parser.h>
// reads file

void parse_line(char *line, t_scene *scene)
{
    char **tokens;

    tokens = ft_split_spaces(line);
    if (!tokens || !tokens[0])
    {
        if (tokens)
            free_split(tokens, count_tokens(tokens));
        return;
    }
    if (!ft_strncmp(tokens[0], "R", 1))
        parse_resolution(tokens, scene);
    else if (!ft_strncmp(tokens[0], "A", 1))
        parse_ambient(tokens, scene);
    else if (!ft_strncmp(tokens[0], "C", 1))
        parse_camera(tokens, scene);
    else if (!ft_strncmp(tokens[0], "L", 1))
        parse_light(tokens, scene);
    else if (!ft_strncmp(tokens[0], "sp", 2))
        parse_sphere(tokens, scene);
    else if (!ft_strncmp(tokens[0], "pl", 2))
        parse_plane(tokens, scene);
    else if (!ft_strncmp(tokens[0], "sq", 2))
        parse_square(tokens, scene);
    else if (!ft_strncmp(tokens[0], "cy", 2))
        parse_cylinder(tokens, scene);
    // else if (!ft_strncmp(tokens[0], "tr", 2))
    //     parse_triangle(tokens, scene);
    else
        error("Unknown identifier");
    free_split(tokens, count_tokens(tokens));
}

int parse_scene(char *filename, t_scene *scene)
{
    int fd;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error("Failed to open file");
    while ((line = get_next_line(fd)))
    {
        parse_line(line, scene);
        free(line);
    }
    close(fd);
    return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:09 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/22 12:36:51 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>
#include <utils.h>

static int	parse_identifier(char **tokens, t_scene *scene)
{
	if (!ft_strncmp(tokens[0], "A", 2))
		return (parse_ambient(tokens, scene));
	else if (!ft_strncmp(tokens[0], "C", 2))
		return (parse_camera(tokens, scene));
	else if (!ft_strncmp(tokens[0], "L", 2))
		return (parse_light(tokens, scene));
	else if (!ft_strncmp(tokens[0], "sp", 3))
		return (parse_sphere(tokens, scene));
	else if (!ft_strncmp(tokens[0], "pl", 3))
		return (parse_plane(tokens, scene));
	else if (!ft_strncmp(tokens[0], "cy", 3))
		return (parse_cylinder(tokens, scene));
	scene->error_msg = "Unknown identifier";
	return (0);
}

int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		result;

	tokens = ft_split_spaces(line);
	if (!tokens)
	{
		scene->error_msg = "Malloc failed";
		return (0);
	}
	if (!tokens[0])
	{
		free_split(tokens, count_tokens(tokens));
		return (1);
	}
	result = parse_identifier(tokens, scene);
	free_split(tokens, count_tokens(tokens));
	return (result);
}

static int	check_filename(char *filename, t_scene *scene)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 3, ".rt", 4) != 0)
	{
		scene->error_msg = "Invalid file extension";
		return (0);
	}
	return (1);
}

int	parse_scene(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	init_scene(scene);
	if (!check_filename(filename, scene))
		error(scene, scene->error_msg);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error(scene, "Failed to open file");
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, scene))
		{
			free(line);
			close(fd);
			error(scene, scene->error_msg);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	validate_scene(scene);
	return (1);
}

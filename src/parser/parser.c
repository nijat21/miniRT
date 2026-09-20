/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:09 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 20:27:08 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>
#include <utils.h>

// this one doesnt need norminette its just for parsing debugging
void print_scene(t_scene *scene)
{
	t_list *current;
	t_obj *obj;
	t_sph *sp;
	t_plane *pl;
	t_cyl *cyl;

	printf("\n");
	printf("========== PARSED SCENE ==========\n");
	printf("\n[AMBIENT]\n");
	printf("has_amb : %d\n", scene->has_amb);
	if (scene->has_amb)
	{
		printf("ratio : %.6f\n", scene->amb.ratio);
		printf("color : %.6f,%.6f,%.6f\n",
			   scene->amb.rgb.x,
			   scene->amb.rgb.y,
			   scene->amb.rgb.z);
	}
	printf("\n[CAMERA]\n");
	printf("has_cam : %d\n", scene->has_cam);
	if (scene->has_cam)
	{
		print_vec("position", scene->cam.cors);
		printf("\n");
		print_vec("orientation", scene->cam.norm);
		printf("\n");
		printf("fov: %.6f\n", scene->cam.hfov);
	}
	printf("\n[LIGHT]\n");
	printf("has_light : %d\n", scene->has_light);
	if (scene->has_light)
	{
		print_vec("position", scene->light.cors);
		printf("\n");
		printf("brightness: %.6f\n", scene->light.brightness);
		printf("color : %.6f,%.6f,%.6f\n",
			   scene->light.rgb.x,
			   scene->light.rgb.y,
			   scene->light.rgb.z);
	}
	printf("\n[OBJECTS]\n");
	current = scene->objs;
	while (current)
	{
		obj = (t_obj *)current->content;
		printf("\nobject type: %d\n", obj->type);
		if (obj->type == SPHERE)
		{
			sp = (t_sph *)obj->data;
			print_vec("position", sp->cors);
			printf("\n");
			printf("radius   : %.6f\n", sp->rad);
			printf("color    : %.6f,%.6f,%.6f\n",
				   sp->rgb.x,
				   sp->rgb.y,
				   sp->rgb.z);
		}
		else if (obj->type == PLANE)
		{
			pl = (t_plane *)obj->data;
			print_vec("position", pl->cors);
			printf("\n");
			print_vec("normal", pl->norm);
			printf("\n");
			printf("color    : %.6f,%.6f,%.6f\n",
				   pl->rgb.x,
				   pl->rgb.y,
				   pl->rgb.z);
		}
		else if (obj->type == CYLINDER)
		{
			cyl = (t_cyl *)obj->data;
			print_vec("position", cyl->cors);
			printf("\n");
			print_vec("normal", cyl->norm);
			printf("\n");
			printf("diameter : %.6f\n", cyl->rad * 2.0);
			printf("height   : %.6f\n", cyl->h);
			printf("color    : %.6f,%.6f,%.6f\n",
				   cyl->rgb.x,
				   cyl->rgb.y,
				   cyl->rgb.z);
		}
		current = current->next;
	}
	printf("\n==================================\n\n");
}

static void parse_identifier(char **tokens, t_scene *scene)
{
	if (!ft_strncmp(tokens[0], "A", 2))
		parse_ambient(tokens, scene);
	else if (!ft_strncmp(tokens[0], "C", 2))
		parse_camera(tokens, scene);
	else if (!ft_strncmp(tokens[0], "L", 2))
		parse_light(tokens, scene);
	else if (!ft_strncmp(tokens[0], "sp", 3))
		parse_sphere(tokens, scene);
	else if (!ft_strncmp(tokens[0], "pl", 3))
		parse_plane(tokens, scene);
	else if (!ft_strncmp(tokens[0], "cy", 3))
		parse_cylinder(tokens, scene);
	else
	{
		free_split(tokens, count_tokens(tokens));
		error(scene, "Unknown identifier");
	}
}

void parse_line(char *line, t_scene *scene)
{
	char **tokens;

	tokens = ft_split_spaces(line);
	if (!tokens)
		error(scene, "Malloc failed");
	if (!tokens[0])
	{
		free_split(tokens, count_tokens(tokens));
		return;
	}
	parse_identifier(tokens, scene);
	free_split(tokens, count_tokens(tokens));
}

int parse_scene(char *filename, t_scene *scene)
{
	int fd;
	char *line;

	init_scene(scene);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error(scene, "Failed to open file");
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	validate_scene(scene);
	// print_scene(scene);
	// clean_scene(scene);
	return (1);
}

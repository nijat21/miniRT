/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:34 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 18:25:35 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>
#include <libft.h>
/*

cy  50.0,0.0,20.6 0,0,1.0   14.2 21.42  10,0,255

tokens[1] center of base of cylinder // better to use middle of cylinder!!!
tokens[2] normal vector
tokens[3] cylinder diameter
tokens[4] cylinder height
tokens[5] color

*/

static void	check_cylinder_norm(t_vec norm, t_scene *scene)
{
	if (norm.x < -1.0 || norm.x > 1.0
		|| norm.y < -1.0 || norm.y > 1.0
		|| norm.z < -1.0 || norm.z > 1.0)
		error(scene, "Cylinder orientation must be in range [-1,1]");
	if (vec_len(norm) == 0.0)
		error(scene, "Cylinder norm cannot be zero");
}

static t_cyl	*init_cyl(char **tokens, t_scene *scene)
{
	t_cyl	*cy;

	cy = malloc(sizeof(t_cyl));
	if (!cy)
		error(scene, "Malloc failed");
	cy->cors = parse_vec(tokens[1], scene);
	cy->norm = parse_vec(tokens[2], scene);
	check_cylinder_norm(cy->norm, scene);
	cy->norm = normalize(cy->norm);
	cy->rad = parse_double(tokens[3], scene) / 2.0;
	cy->h = parse_double(tokens[4], scene);
	if (cy->rad <= 0 || cy->h <= 0)
	{
		free(cy);
		error(scene, "Cylinder diameter and height must be > 0");
	}
	cy->half_h = cy->h / 2.0;
	cy->rgb = parse_color(tokens[5], scene);
	return (cy);
}

void	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cyl	*cy;

	if (count_tokens(tokens) != 6)
		error(scene, "Invalid cylinder format");
	cy = init_cyl(tokens, scene);
	add_obj(scene, CYLINDER, cy);
}

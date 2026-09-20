/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:34 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/21 00:08:41 by abraz-ab         ###   ########.fr       */
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

static int	parse_cylinder_color(char *token, t_cyl *cy, t_scene *scene)
{
	if (!parse_color(token, &cy->rgb, scene))
	{
		scene->error_msg = "Invalid color";
		return (0);
	}
	return (1);
}

static t_cyl	*init_cyl(char **tokens, t_scene *scene)
{
	t_cyl	*cy;

	cy = malloc(sizeof(t_cyl));
	if (!cy)
	{
		scene->error_msg = "Malloc failed";
		return (NULL);
	}
	if (!parse_cylinder_vectors(tokens, cy, scene)
		|| !parse_cylinder_size(tokens, cy, scene)
		|| !parse_cylinder_color(tokens[5], cy, scene))
	{
		free(cy);
		return (NULL);
	}
	return (cy);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cyl	*cy;

	if (count_tokens(tokens) != 6)
	{
		scene->error_msg = "Invalid cylinder format";
		return (0);
	}
	cy = init_cyl(tokens, scene);
	if (!cy)
		return (0);
	add_obj(scene, CYLINDER, cy);
	return (1);
}

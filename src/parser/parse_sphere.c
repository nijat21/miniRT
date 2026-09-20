/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:43 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/21 00:13:53 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>
#include <libft.h>

static int	parse_sphere_position(char *token, t_sph *sp, t_scene *scene)
{
	if (!parse_vec(token, &sp->cors, scene))
	{
		scene->error_msg = "Invalid position";
		return (0);
	}
	return (1);
}

static int	parse_sphere_diameter(char *token, t_sph *sp, t_scene *scene)
{
	double	diameter;

	if (!parse_double(token, &diameter))
	{
		scene->error_msg = "Invalid number";
		return (0);
	}
	if (diameter <= 0.0)
	{
		scene->error_msg = "Sphere diameter must be greater than 0";
		return (0);
	}
	sp->rad = diameter / 2.0;
	return (1);
}

static int	parse_sphere_color(char *token, t_sph *sp, t_scene *scene)
{
	if (!parse_color(token, &sp->rgb, scene))
	{
		scene->error_msg = "Invalid color";
		return (0);
	}
	return (1);
}

static t_sph	*init_sph(char **tokens, t_scene *scene)
{
	t_sph	*sp;

	sp = malloc(sizeof(t_sph));
	if (!sp)
	{
		scene->error_msg = "Malloc failed";
		return (NULL);
	}
	if (!parse_sphere_position(tokens[1], sp, scene)
		|| !parse_sphere_diameter(tokens[2], sp, scene)
		|| !parse_sphere_color(tokens[3], sp, scene))
	{
		free(sp);
		return (NULL);
	}
	return (sp);
}

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_sph	*sp;

	if (count_tokens(tokens) != 4)
	{
		scene->error_msg = "Invalid sphere format";
		return (0);
	}
	sp = init_sph(tokens, scene);
	if (!sp)
		return (0);
	add_obj(scene, SPHERE, sp);
	return (1);
}

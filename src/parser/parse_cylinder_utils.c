/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 00:03:47 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/21 00:03:48 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>
#include <libft.h>

int	check_cylinder_norm(t_vec norm, t_scene *scene)
{
	if (norm.x < -1.0 || norm.x > 1.0
		|| norm.y < -1.0 || norm.y > 1.0
		|| norm.z < -1.0 || norm.z > 1.0)
	{
		scene->error_msg = "Cylinder orientation must be in range [-1.0,1.0]";
		return (0);
	}
	if (vec_len(norm) == 0.0)
	{
		scene->error_msg = "Cylinder orientation cannot be zero";
		return (0);
	}
	return (1);
}

int	parse_cylinder_vectors(char **tokens, t_cyl *cy, t_scene *scene)
{
	if (!parse_vec(tokens[1], &cy->cors, scene))
	{
		scene->error_msg = "Invalid position";
		return (0);
	}
	if (!parse_vec(tokens[2], &cy->norm, scene))
	{
		scene->error_msg = "Invalid orientation";
		return (0);
	}
	if (!check_cylinder_norm(cy->norm, scene))
		return (0);
	cy->norm = normalize(cy->norm);
	return (1);
}

int	parse_cylinder_size(char **tokens, t_cyl *cy, t_scene *scene)
{
	double	diameter;

	if (!parse_double(tokens[3], &diameter) || diameter <= 0.0)
	{
		scene->error_msg = "Invalid cylinder diameter";
		return (0);
	}
	cy->rad = diameter / 2.0;
	if (!parse_double(tokens[4], &cy->h) || cy->h <= 0.0)
	{
		scene->error_msg = "Invalid cylinder height";
		return (0);
	}
	cy->half_h = cy->h / 2.0;
	return (1);
}

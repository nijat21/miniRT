/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:40 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/22 13:33:40 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>
#include <libft.h>
/*

pl 0,0,0 0,1,0 255,255,255

tokens[1] point on plane
tokens[2] normal vector
tokens[3] color

*/

static int	check_plane_norm(t_vec norm, t_scene *scene)
{
	double	len;

	if (norm.x < -1.0 || norm.x > 1.0
		|| norm.y < -1.0 || norm.y > 1.0
		|| norm.z < -1.0 || norm.z > 1.0)
	{
		scene->error_msg = "Plane orientation must be in range [-1.0,1.0]";
		return (0);
	}
	len = vec_len(norm);
	if (len == 0.0)
	{
		scene->error_msg = "Plane orientation cannot be zero";
		return (0);
	}
	if (len > 1)
	{
		scene->error_msg = "Plane orientation must be normalized";
		return (0);
	}
	return (1);
}

static int	parse_plane_vectors(char **tokens, t_plane *pl, t_scene *scene)
{
	if (!parse_vec(tokens[1], &pl->cors, scene))
	{
		scene->error_msg = "Invalid position";
		return (0);
	}
	if (!parse_vec(tokens[2], &pl->norm, scene))
	{
		scene->error_msg = "Invalid orientation";
		return (0);
	}
	if (!check_plane_norm(pl->norm, scene))
		return (0);
	return (1);
}

static int	parse_plane_color(char *token, t_plane *pl, t_scene *scene)
{
	if (!parse_color(token, &pl->rgb, scene))
	{
		scene->error_msg = "Invalid color";
		return (0);
	}
	return (1);
}

static t_plane	*init_plane(char **tokens, t_scene *scene)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		scene->error_msg = "Malloc failed";
		return (NULL);
	}
	if (!parse_plane_vectors(tokens, pl, scene)
		|| !parse_plane_color(tokens[3], pl, scene))
	{
		free(pl);
		return (NULL);
	}
	return (pl);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*pl;

	if (count_tokens(tokens) != 4)
	{
		scene->error_msg = "Invalid plane format";
		return (0);
	}
	pl = init_plane(tokens, scene);
	if (!pl)
		return (0);
	add_obj(scene, PLANE, pl);
	return (1);
}

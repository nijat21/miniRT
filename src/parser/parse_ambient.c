/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:25 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/21 00:06:33 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>

/*

A 0.2 255,255,255

Tokens:
[0] = "A"
[1] = ratio (double)
[2] = color

*/

static int	check_ambient_format(char **tokens, t_scene *scene)
{
	if (scene->has_amb)
	{
		scene->error_msg = "Ambient already defined";
		return (0);
	}
	if (count_tokens(tokens) != 3)
	{
		scene->error_msg = "Invalid ambient format";
		return (0);
	}
	return (1);
}

static int	check_ambient_ratio(char *token, t_scene *scene)
{
	if (!parse_double(token, &scene->amb.ratio))
	{
		scene->error_msg = "Invalid number";
		return (0);
	}
	if (scene->amb.ratio < 0.0 || scene->amb.ratio > 1.0)
	{
		scene->error_msg = "Ambient ratio must be in range [0.0,1.0]";
		return (0);
	}
	return (1);
}

static int	check_ambient_color(char *token, t_scene *scene)
{
	if (!parse_color(token, &scene->amb.rgb, scene))
	{
		scene->error_msg = "Invalid color";
		return (0);
	}
	return (1);
}

int	parse_ambient(char **tokens, t_scene *scene)
{
	if (!check_ambient_format(tokens, scene))
		return (0);
	if (!check_ambient_ratio(tokens[1], scene))
		return (0);
	if (!check_ambient_color(tokens[2], scene))
		return (0);
	scene->has_amb = true;
	return (1);
}

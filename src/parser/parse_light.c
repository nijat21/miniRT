/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:37 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 23:13:36 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>
/*
l -40.0,50.0,0.0 0.6 10,0,255

tokens:

[0] = "l"
[1] = position
[2] = brightness
[3] = color

*/

static int	check_light_format(char **tokens, t_scene *scene)
{
	if (scene->has_light)
	{
		scene->error_msg = "Light already defined";
		return (0);
	}
	if (count_tokens(tokens) != 4)
	{
		scene->error_msg = "Invalid light format";
		return (0);
	}
	return (1);
}

static int	parse_light_brightness(char *token, t_scene *scene)
{
	if (!parse_double(token, &scene->light.brightness))
	{
		scene->error_msg = "Invalid number";
		return (0);
	}
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
	{
		scene->error_msg = "Light brightness must be in range [0.0, 1.0]";
		return (0);
	}
	return (1);
}

int	parse_light(char **tokens, t_scene *scene)
{
	if (!check_light_format(tokens, scene))
		return (0);
	if (!parse_vec(tokens[1], &scene->light.cors, scene))
	{
		scene->error_msg = "Invalid position";
		return (0);
	}
	if (!parse_light_brightness(tokens[2], scene))
		return (0);
	if (!parse_color(tokens[3], &scene->light.rgb, scene))
	{
		scene->error_msg = "Invalid color";
		return (0);
	}
	scene->has_light = true;
	return (1);
}

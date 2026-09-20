/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:37 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 18:25:38 by abraz-ab         ###   ########.fr       */
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

void	parse_light(char **tokens, t_scene *scene)
{
	if (scene->has_light)
		error(scene, "Light already defined");
	if (count_tokens(tokens) != 4)
		error(scene, "Invalid light format");
	scene->light.cors = parse_vec(tokens[1], scene);
	scene->light.brightness = parse_double(tokens[2], scene);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		error(scene, "Light brightness must be in range [0.0,1.0]");
	scene->light.rgb = parse_color(tokens[3], scene);
	scene->has_light = true;
}

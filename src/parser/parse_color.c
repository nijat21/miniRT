/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 23:57:06 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 23:57:07 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>

static int	check_color_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255
		|| b < 0 || b > 255)
		return (0);
	return (1);
}

static int	parse_color_values(char **split, int *r, int *g, int *b)
{
	if (!parse_int(split[0], r)
		|| !parse_int(split[1], g)
		|| !parse_int(split[2], b))
		return (0);
	return (1);
}

static void	set_color(t_vec *color, int r, int g, int b)
{
	color->x = (double)r / 255.0;
	color->y = (double)g / 255.0;
	color->z = (double)b / 255.0;
}

static int	parse_color_data(char **split, t_vec *color, t_scene *scene)
{
	int	r;
	int	g;
	int	b;

	if (count_tokens(split) != 3)
	{
		scene->error_msg = "Invalid color";
		return (0);
	}
	if (!parse_color_values(split, &r, &g, &b))
	{
		scene->error_msg = "Invalid color";
		return (0);
	}
	if (!check_color_range(r, g, b))
	{
		scene->error_msg = "Color values must be in range [0,255]";
		return (0);
	}
	set_color(color, r, g, b);
	return (1);
}

int	parse_color(char *str, t_vec *result, t_scene *scene)
{
	char	**split;

	if (!str)
	{
		scene->error_msg = "Invalid color";
		return (0);
	}
	split = ft_split(str, ',');
	if (!split)
	{
		scene->error_msg = "Malloc failed";
		return (0);
	}
	if (!parse_color_data(split, result, scene))
	{
		free_split(split, count_tokens(split));
		return (0);
	}
	free_split(split, count_tokens(split));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:50 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/22 12:22:00 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>

static int	parse_vec_values(char **split, t_vec *v)
{
	if (!parse_double(split[0], &v->x)
		|| !parse_double(split[1], &v->y)
		|| !parse_double(split[2], &v->z))
		return (0);
	return (1);
}

int	valid_vec_format(char *str)
{
	int	i;
	int	commas;

	if (!str || !*str)
		return (0);
	i = 0;
	commas = 0;
	if (str[0] == ',' || str[ft_strlen(str) - 1] == ',')
		return (0);
	while (str[i])
	{
		if (str[i] == ',')
		{
			commas++;
			if (str[i + 1] == ',')
				return (0);
		}
		i++;
	}
	return (commas == 2);
}

int	parse_vec(char *str, t_vec *result, t_scene *scene)
{
	char	**split;
	t_vec	v;

	if (!valid_vec_format(str))
	{
		scene->error_msg = "Invalid vector";
		return (0);
	}
	split = ft_split(str, ',');
	if (!split)
	{
		scene->error_msg = "Malloc failed";
		return (0);
	}
	if (count_tokens(split) != 3 || !parse_vec_values(split, &v))
	{
		free_split(split, count_tokens(split));
		scene->error_msg = "Invalid vector";
		return (0);
	}
	free_split(split, count_tokens(split));
	*result = v;
	return (1);
}

void	add_obj(t_scene *scene, t_obj_type type, void *data)
{
	t_obj	*obj;
	t_list	*node;

	obj = malloc(sizeof(t_obj));
	if (!obj)
	{
		free(data);
		error(scene, "Malloc failed");
	}
	obj->type = type;
	obj->data = data;
	node = ft_lstnew(obj);
	if (!node)
	{
		free(obj);
		free(data);
		error(scene, "Malloc failed");
	}
	ft_lstadd_back(&scene->objs, node);
}

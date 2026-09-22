/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:05 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 18:29:46 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>

void	validate_scene(t_scene *scene)
{
	if (!scene->has_amb)
		error(scene, "Missing ambient");
	if (!scene->has_cam)
		error(scene, "Missing camera");
	if (!scene->has_light)
		error(scene, "Missing light");
}

void	free_obj(void *content)
{
	t_obj	*obj;

	obj = (t_obj *)content;
	if (!obj)
		return ;
	free(obj->data);
	free(obj);
}

void	clean_scene(t_scene *scene)
{
	if (!scene)
		return ;
	ft_lstclear(&scene->objs, free_obj);
}

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
}

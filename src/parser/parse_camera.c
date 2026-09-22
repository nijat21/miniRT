/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:30 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/22 13:33:21 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>

/*
C 0,0,0 0,0,0 120
*/

static int	check_camera_format(char **tokens, t_scene *scene)
{
	if (scene->has_cam)
	{
		scene->error_msg = "Camera already defined";
		return (0);
	}
	if (count_tokens(tokens) != 4)
	{
		scene->error_msg = "Invalid camera format";
		return (0);
	}
	return (1);
}

static int	check_camera_norm(t_vec norm, t_scene *scene)
{
	double	len;

	if (norm.x < -1.0 || norm.x > 1.0 || norm.y < -1.0 || norm.y > 1.0
		|| norm.z < -1.0 || norm.z > 1.0)
	{
		scene->error_msg = "Camera orientation must be in range [-1,1]";
		return (0);
	}
	len = vec_len(norm);
	if (len == 0.0)
	{
		scene->error_msg = "Camera orientation cannot be zero";
		return (0);
	}
	if (len > 1)
	{
		scene->error_msg = "Camera orientation must be normalized";
		return (0);
	}
	return (1);
}

static int	parse_camera_fov(char *token, t_cam *cam, t_scene *scene)
{
	int	fov;

	if (!parse_int(token, &fov))
	{
		scene->error_msg = "Invalid FOV";
		return (0);
	}
	if (fov < 0 || fov > 180)
	{
		scene->error_msg = "FOV must be in range [0,180]";
		return (0);
	}
	cam->hfov = fov;
	return (1);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	t_cam	cam;

	if (!check_camera_format(tokens, scene))
		return (0);
	if (!parse_vec(tokens[1], &cam.cors, scene))
	{
		scene->error_msg = "Invalid position";
		return (0);
	}
	if (!parse_vec(tokens[2], &cam.norm, scene))
	{
		scene->error_msg = "Invalid orientation";
		return (0);
	}
	if (!check_camera_norm(cam.norm, scene))
		return (0);
	if (!parse_camera_fov(tokens[3], &cam, scene))
		return (0);
	scene->cam = cam;
	scene->has_cam = true;
	return (1);
}

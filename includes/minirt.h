/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:42 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/21 00:27:35 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <vec.h>

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_plane
{
	t_vec		cors;
	t_vec		norm;
	t_vec		rgb;
}				t_plane;

typedef struct s_square
{
	t_vec		cors;
	t_vec		norm;
	double		side_len;
	t_vec		rgb;
}				t_square;

typedef struct s_sph
{
	t_vec		cors;
	double		rad;
	t_vec		rgb;
}				t_sph;

typedef struct s_circle
{
	t_vec		cors;
	t_vec		norm;
	double		rad;
}				t_circle;

typedef struct s_cyl
{
	t_vec		cors;
	t_vec		norm;
	double		h;
	double		half_h;
	double		rad;
	t_vec		rgb;
}				t_cyl;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
	SQUARE
}				t_obj_type;

typedef struct s_obj
{
	t_obj_type	type;
	void		*data;
}				t_obj;

typedef struct s_amb
{
	double		ratio;
	t_vec		rgb;
}				t_amb;

typedef struct s_light
{
	t_vec		cors;
	double		brightness;
	t_vec		rgb;
}				t_light;

typedef struct s_cam
{
	t_vec		cors;
	t_vec		norm;
	t_vec		right;
	t_vec		up;
	double		hfov;
}				t_cam;

typedef struct s_scene
{
	int			w;
	int			h;

	t_amb		amb;
	t_cam		cam;
	t_light		light;
	t_list		*objs;

    bool has_res;
    bool has_amb;
    bool has_cam;
    bool has_light;

    char *error_msg;
} t_scene;

#endif // MINIRT_H

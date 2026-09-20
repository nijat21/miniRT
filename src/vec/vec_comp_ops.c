/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_comp_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:54:14 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 20:55:12 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <vec.h>

t_vec	vec_scal_mul(t_vec a, double k)
{
	return (create_vec(a.x * k, a.y * k, a.z * k));
}

t_vec	vec_scal_div(t_vec a, double k)
{
	return (create_vec(a.x / k, a.y / k, a.z / k));
}

double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// cross product isn't commutative
t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	vec;
	double	len;

	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	len = vec_len(vec);
	return (vec_scal_div(vec, len));
}

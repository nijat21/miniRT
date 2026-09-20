/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:54:16 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 20:55:14 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <vec.h>

t_vec vec_add(t_vec a, t_vec b)
{
    return create_vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec vec_sub(t_vec a, t_vec b)
{
    return create_vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

t_vec vec_mul(t_vec a, t_vec b)
{
    return create_vec(a.x * b.x, a.y * b.y, a.z * b.z);
}

t_vec vec_div(t_vec a, t_vec b)
{
    return create_vec(a.x / b.x, a.y / b.y, a.z / b.z);
}

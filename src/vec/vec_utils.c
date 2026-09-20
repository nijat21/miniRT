/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:54:20 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 20:55:16 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <vec.h>

t_vec create_vec(double x, double y, double z)
{
    t_vec vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

double vec_len(t_vec a)
{
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

t_vec normalize(t_vec vec)
{
    double len;

    len = vec_len(vec);
    if (len == 0.0)
        return create_vec(0, 0, 0);
    return vec_scal_div(vec, len);
}

/*
    Cauchy-Schwarz inequality guarantees that no two normalised vectors
    may have dot product bigger than 1
    EPSILON = 0.000001 -> floating-point error
*/
bool vec_par_norm(t_vec va, t_vec vb)
{
    return fabs(vec_dot(va, vb)) >= (1.0 - EPSILON);
}
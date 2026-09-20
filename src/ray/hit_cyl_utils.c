/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cyl_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:53:56 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 20:55:09 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <minirt.h>
#include <ray.h>

bool select_cyl_t(double ts[], t_cyl_part labels[], double *t, t_cyl_part *part_hit)
{
    bool a_valid;
    bool b_valid;

    a_valid = ts[0] > EPSILON;
    b_valid = ts[1] > EPSILON;
    if (!a_valid && !b_valid)
        return (false);
    if (a_valid && (!b_valid || ts[0] < ts[1]))
    {
        *t = ts[0];
        *part_hit = labels[0];
    }
    else
    {
        *t = ts[1];
        *part_hit = labels[1];
    }
    return (true);
}
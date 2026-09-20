/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:53:36 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 20:56:36 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>
#include <stdio.h>
#include <vec.h>

void	print_vec(const char *name, t_vec v)
{
	printf("    %s: (%.17g, %.17g, %.17g)\n", name, v.x, v.y, v.z);
}

void	dbl_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	print_cyl_part(t_cyl_part part)
{
	if (part == SIDE)
		printf("SIDE\n");
	else if (part == TOP)
		printf("TOP\n");
	else if (part == BTM)
		printf("BTM\n");
	else
		printf("UNKNOWN\n");
}

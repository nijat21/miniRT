/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:27:00 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 18:27:01 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
#define VEC_H

#define EPSILON 1e-6

#include <stdbool.h>

typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;

t_vec create_vec(double x, double y, double z);
t_vec vec_add(t_vec a, t_vec b);
t_vec vec_sub(t_vec a, t_vec b);
t_vec vec_mul(t_vec a, t_vec b);
t_vec vec_div(t_vec a, t_vec b);
t_vec vec_scal_mul(t_vec a, double k);
t_vec vec_scal_div(t_vec a, double k);
double vec_dot(t_vec a, t_vec b);
t_vec vec_cross(t_vec a, t_vec b);

// ------includes/vec.h----------------------------------------------
double vec_len(t_vec a);
t_vec normalize(t_vec vec);
bool vec_par_norm(t_vec a, t_vec b);
bool vec_perp_norm(t_vec a, t_vec b);

#endif
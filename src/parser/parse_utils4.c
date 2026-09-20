/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:00 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 19:48:33 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>

static int	get_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

static int	check_digit(char c, long *val)
{
	if (!ft_isdigit(c))
		return (0);
	*val = *val * 10 + (c - '0');
	if (*val > 2147483647L)
		return (0);
	return (1);
}

int	parse_int(char *str, int *result)
{
	int		i;
	int		sign;
	long	val;

	i = 0;
	val = 0;
	if (!str || !str[0])
		return (0);
	sign = get_sign(str[i]);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!check_digit(str[i], &val))
			return (0);
		i++;
	}
	*result = (int)(val * sign);
	return (1);
}

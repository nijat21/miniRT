/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:53:11 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 22:40:06 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error_handler.h>
#include <libft.h>
#include <stdbool.h>

char	*err_msg(t_error err)
{
	if (err == ERR_INVALID_INPUT)
		return ("Input is invalid");
	if (err == ERR_INVALID_ARG)
		return ("Argument is invalid");
	if (err == ERR_MALLOC)
		return ("Memory couldn't be allocated");
	if (err == ERR_MLX_WIN)
		return ("Mlx window generation failure");
	if (err == ERR_MLX_IMG)
		return ("Mlx image generation failure");
	if (err == ERR_MLX_IMG_ADDR)
		return ("Mlx image address failure");
	if (err == ERR_INPUT_FORMAT)
		return ("Error\nUsage: ./miniRT file.rt");
	if (err == ERR_PARSING_FAILED)
		return ("Error\nParsing failed");
	if (err == ERR_WRONG_OBJ)
		return ("Wrong object type");
	else
		return ("Some other error");
}

void	def_err(void)
{
	ft_putstr_fd("Something went wrong", 2);
	ft_putstr_fd("\n", 2);
}

void	print_err_msg(const char *msg)
{
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
}

void	print_err(const t_error err)
{
	ft_putstr_fd(err_msg(err), 2);
	ft_putstr_fd("\n", 2);
}

bool	return_err(const t_error err)
{
	ft_putstr_fd(err_msg(err), 2);
	ft_putstr_fd("\n", 2);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 20:53:11 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/20 20:53:12 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <error_handler.h>
#include <libft.h>

char *err_msg(t_error err)
{
    switch (err)
    {
    case ERR_INVALID_INPUT:
        return ("Input is invalid");
    case ERR_INVALID_ARG:
        return ("Argument is invalid");
    case ERR_MALLOC:
        return ("Memory couldn't be allocated");
    case ERR_MLX_WIN:
        return ("Mlx window generation failure");
    case ERR_MLX_IMG:
        return ("Mlx image generation failure");
    case ERR_MLX_IMG_ADDR:
        return ("Mlx image address failure");
    case ERR_INPUT_FORMAT:
        return ("Error\nUsage: ./miniRT file.rt");
    case ERR_PARSING_FAILED:
        return ("Error\nParsing failed");
    case ERR_WRONG_OBJ:
        return ("Wrong object type");
    default:
        return ("Some other error");
    }
}

void def_err()
{
    ft_putstr_fd("Something went wrong", 2);
    ft_putstr_fd("\n", 2);
}

void print_err_msg(const char *msg)
{
    ft_putstr_fd((char *)msg, 2);
    ft_putstr_fd("\n", 2);
}

void print_err(const t_error err)
{
    ft_putstr_fd(err_msg(err), 2);
    ft_putstr_fd("\n", 2);
}

bool return_err(const t_error err)
{
    ft_putstr_fd(err_msg(err), 2);
    ft_putstr_fd("\n", 2);
    return false;
}

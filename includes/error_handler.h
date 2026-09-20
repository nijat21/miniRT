/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:39 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 22:54:15 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include <stdbool.h>

typedef enum e_error
{
	ERR_INVALID_INPUT,
	ERR_INVALID_ARG,
	ERR_MALLOC,
	ERR_MLX_WIN,
	ERR_MLX_IMG,
	ERR_MLX_IMG_ADDR,
	ERR_INPUT_FORMAT,
	ERR_PARSING_FAILED,
	ERR_WRONG_OBJ,
}		t_error;

void	def_err(void);
void	print_err_msg(const char *msg);
void	print_err(const t_error err);
bool	return_err(const t_error err);

#endif

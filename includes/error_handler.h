/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:39 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 18:26:40 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANLDER_H
#define ERROR_HANLDER_H

#include <stdbool.h>

typedef enum e_error
{
    // General
    ERR_INVALID_INPUT,
    ERR_INVALID_ARG,
    ERR_MALLOC,
    // Window related
    ERR_MLX_WIN,
    ERR_MLX_IMG,
    ERR_MLX_IMG_ADDR,
    // Parsing
    ERR_INPUT_FORMAT,
    ERR_PARSING_FAILED,
    // Functional
    ERR_WRONG_OBJ,
} t_error;

void def_err();
void print_err_msg(const char *msg);
void print_err(const t_error err);
bool return_err(const t_error err);

#endif

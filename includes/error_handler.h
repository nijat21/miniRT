#ifndef ERROR_HANLDER_H
#define ERROR_HANLDER_H

typedef enum e_error {
    // General
    ERR_INVALID_INPUT,
    ERR_INVALID_ARG,
    ERR_MALLOC,
    // Window related
    ERR_MLX_WIN,
    ERR_MLX_IMG,
    ERR_MLX_IMG_ADDR,
} t_error;

void print_err(const t_error err);

#endif

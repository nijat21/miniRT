#include <stdbool.h>
#include <error_handler.h>
#include <libft.h>

char *err_msg(t_error err)
{
    switch (err)
    {
    // General
    case ERR_INVALID_INPUT:
        return ("Input is invalid");
    case ERR_INVALID_ARG:
        return ("Argument is invalid");
    case ERR_MALLOC:
        return ("Memory couldn't be allocated");
    // Window related
    case ERR_MLX_WIN:
        return ("Mlx window generation failure");
    case ERR_MLX_IMG:
        return ("Mlx image generation failure");
    case ERR_MLX_IMG_ADDR:
        return ("Mlx image address failure");
    case ERR_WRONG_OBJ:
        return ("Wrong object type");
    default:
        return ("Some other error");
    }
}

void def_err()
{
    ft_putstr_fd("Something went wrong", 2);
}

void print_err_msg(const char *msg)
{
    ft_putstr_fd(msg, 2);
}

void print_err(const t_error err)
{
    ft_putstr_fd(err_msg(err), 2);
}

bool return_err(const t_error err)
{
    ft_putstr_fd(err_msg(err), 2);
    return false;
}

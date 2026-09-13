#include <error_handler.h>
#include <libft.h>
#include <window.h>

t_disp *disp_init(const int width, const int height)
{
    t_disp *disp;

    if (width <= 0 || height <= 0)
    {
        print_err(ERR_INVALID_ARG);
        return NULL;
    }
    disp = malloc(sizeof(t_disp));
    if (!disp)
    {
        print_err(ERR_MALLOC);
        return NULL;
    }
    disp->w = width;
    disp->h = height;
    disp->win = NULL;
    disp->img = NULL;
    disp->mlx = mlx_init();
    if (!disp->mlx)
    {
        print_err(ERR_MLX_WIN);
        free(disp);
        return NULL;
    }
    return disp;
}

t_win *win_init(t_disp *disp)
{
    t_win *win;

    if (!disp->mlx)
    {
        print_err(ERR_INVALID_ARG);
        return NULL;
    }
    win = malloc(sizeof(t_win));
    if (!win)
    {
        print_err(ERR_MALLOC);
        return NULL;
    }
    win->win = mlx_new_window(disp->mlx, disp->w, disp->h, "MiniRT");
    if (!win->win)
    {
        print_err(ERR_MLX_WIN);
        free(win);
        return NULL;
    }
    return win;
}

t_img *img_data(t_disp *disp, t_img *img)
{
    img->addr = mlx_get_data_addr(img->img, &(img->bits_pp), &(img->line_len), &(img->endian));
    if (!img->addr)
    {
        print_err(ERR_MLX_IMG_ADDR);
        mlx_destroy_image(disp->mlx, img->img);
        free(img);
        return NULL;
    }
    return img;
}

t_img *img_init(t_disp *disp)
{
    t_img *img;

    if (!disp->mlx)
    {
        print_err(ERR_INVALID_ARG);
        return NULL;
    }
    img = malloc(sizeof(t_img));
    if (!img)
    {
        print_err(ERR_MALLOC);
        return NULL;
    }
    img->img = mlx_new_image(disp->mlx, disp->w, disp->h);
    if (!img->img)
    {
        print_err(ERR_MLX_IMG);
        free(img);
        return NULL;
    }
    return img_data(disp, img);
}

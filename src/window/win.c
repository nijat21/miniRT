#include <error_handler.h>
#include <libft.h>
#include <window.h>

t_disp *disp_init() {
    t_disp *disp;

    disp = malloc(sizeof(t_disp));
    if (!disp) {
        print_err(ERR_MALLOC);
        return NULL;
    }
    disp->win = NULL;
    disp->img = NULL;
    disp->mlx = NULL;
    disp->mlx = mlx_init();
    if (!disp->mlx) {
        print_err(ERR_MLX_WIN);
        free(disp);
        return NULL;
    }
    return disp;
}

t_win *win_init(void *mlx, const int width, const int height) {
    t_win *win;

    if (width <= 0 || height <= 0) {
        print_err(ERR_INVALID_ARG);
        return NULL;
    }
    win = malloc(sizeof(t_win));
    if (!win) {
        print_err(ERR_MALLOC);
        return NULL;
    }
    win->width = width;
    win->height = height;
    win->win = mlx_new_window(mlx, width, height, "MiniRT");
    if (!win->win) {
        print_err(ERR_MLX_WIN);
        free(win);
        return NULL;
    }
    return win;
}

t_img *img_init(void *mlx, const int width, const int height) {
    t_img *img;

    if (!mlx || width <= 0 || height <= 0) {
        print_err(ERR_INVALID_ARG);
        return NULL;
    }
    img = malloc(sizeof(t_img));
    if (!img) {
        print_err(ERR_MALLOC);
        return NULL;
    }
    img->img = mlx_new_image(mlx, width, height);
    if (!img->img) {
        print_err(ERR_MLX_IMG);
        free(img);
        return NULL;
    }
    img->width = width;
    img->height = height;
    img->addr = mlx_get_data_addr(img->img, &(img->bits_pp), &(img->line_len), &(img->endian));
    if (!img->addr) {
        print_err(ERR_MLX_IMG_ADDR);
        mlx_destroy_image(mlx, img->img);
        free(img);
        return NULL;
    }
    return img;
}

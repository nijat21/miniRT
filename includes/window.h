#ifndef WINDOW_H
#define WINDOW_H

#if defined(__APPLE__)
#include "minilibx_macos_metal/mlx.h"
#elif defined(__linux__)
#include "minilibx-linux/mlx.h"
#else
#error "Unsupported OS"
#endif

typedef struct s_img {
    void *img;
    char *addr;
    int bits_pp;
    int line_len;
    int endian;
    int width;
    int height;
} t_img;

typedef struct s_win {
    void *win;
    int width;
    int height;
} t_win;

typedef struct s_disp {
    void *mlx;
    t_win *win;
    t_img *img;
} t_disp;

t_disp *disp_init();
t_win *win_init(void *mlx, const int width, const int height);
t_img *img_init(void *mlx, const int width, const int height);

void cleanup(t_disp *disp);
int close_win(t_disp *disp);
int key_hook(int keycode, t_disp *disp);

#endif

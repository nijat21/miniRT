#ifndef WINDOW_H
#define WINDOW_H

#if defined(__APPLE__)
#include "../minilibx_macos_metal/mlx.h"
#define KEY_ESC 53
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_PRESS_MASK 0
#define KEY_RELEASE_MASK 0
#define MOUSE_PRESS_MASK 0
#define MOUSE_RELEASE_MASK 0
#define MOTION_MASK 0
#elif defined(__linux__)
#include "../minilibx-linux/mlx.h"
#include <X11/keysym.h>
#define KEY_ESC XK_Escape
#define KEY_LEFT XK_Left
#define KEY_RIGHT XK_Right
#define KEY_PRESS_MASK (1L << 0)
#define KEY_RELEASE_MASK (1L << 1)
#define MOUSE_PRESS_MASK (1L << 2)
#define MOUSE_RELEASE_MASK (1L << 3)
#define MOTION_MASK (1L << 6)
#else
#error "Unsupported OS"
#endif

#include <minirt.h>

typedef struct s_img
{
    void *img;
    char *addr;
    int bits_pp;
    int line_len;
    int endian;
} t_img;

typedef struct s_win
{
    void *win;
} t_win;

typedef struct s_disp
{
    void *mlx;
    t_win *win;
    t_img *img;
    int w;
    int h;
} t_disp;

//---src/window/win.c-----------------------------------------------------
t_disp *disp_init(const int width, const int height);
t_win *win_init(t_disp *disp);
t_img *img_init(t_disp *disp);

//---src/window/hooks.c-----------------------------------------------------
void cleanup(t_disp *disp);
int close_win(t_disp *disp);
int key_hook(int keycode, t_disp *disp);

//---src/window/drawer.c-----------------------------------------------------
void color_px(t_img *img, int x, int y, t_rgb rgb);

#endif

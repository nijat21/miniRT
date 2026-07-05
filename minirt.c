#include <error_handler.h>
#include <stdlib.h>
#include <window.h>

/* void	my_mlx_pixel_put(t_img* img, int x, int y, int color) */
/* { */
/* 	char	*dst; */

/* 	dst = img->addr + (y * img->line_len + x * (img->bits_pp / 8)); */
/* 	*(unsigned int*)dst = color; */
/* } */

int main() {
    t_disp *disp;

    disp = disp_init();
    if (!disp)
        return EXIT_FAILURE;
    disp->win = win_init(disp->mlx, 1336, 768);
    if (!disp->win) {
        cleanup(disp);
        return EXIT_FAILURE;
    }
    disp->img = img_init(disp->mlx, 1336, 768);
    if (!disp->img) {
        cleanup(disp);
        return EXIT_FAILURE;
    }

    /* my_mlx_pixel_put(img->img, 5, 5, 0x00FF0000); */
    mlx_put_image_to_window(disp->mlx, disp->win->win, disp->img->img, 0, 0);

    // mlx_hook(win, 2, 1L << 0, key_press, data);   // KeyPressMask
    // mlx_hook(win, 3, 1L << 1, key_release, data); // KeyReleaseMask
    // mlx_hook(win, 4, 1L << 2, mouse_press, data); // ButtonPressMask
    // mlx_hook(win, 6, 1L << 6, mouse_move, data);  // PointerMotionMask
    mlx_key_hook(disp->win->win, key_hook, disp);
    mlx_hook(disp->win->win, 17, 0, close_win, disp);

    mlx_loop(disp->mlx);
}

#include "includes/error_handler.h"
#include "includes/minirt.h"
#include "includes/parser.h"
#include "includes/ray.h"
#include <stdio.h>
#include "includes/window.h"

int main(int ac, char **av)
{
    t_disp *disp;
    t_scene scene;

    if (ac != 2)
        return (printf("Error\nUsage: ./miniRT file.rt\n"), 1);
    if (!parse_scene(av[1], &scene))
        return (printf("Error\nParsing failed\n"), 1);

    disp = disp_init(1336, 768);
    if (!disp)
        return EXIT_FAILURE;

    // disp->win = win_init(disp);
    // if (!disp->win) {
    //     cleanup(disp);
    //     return EXIT_FAILURE;
    // }
    // disp->img = img_init(disp);
    // if (!disp->img) {
    //     cleanup(disp);
    //     return EXIT_FAILURE;
    // }

    // mlx_put_image_to_window(disp->mlx, disp->win->win, disp->img->img, 0, 0);

    // mlx_key_hook(disp->win->win, key_hook, disp);
    // mlx_hook(disp->win->win, 17, 0, close_win, disp);
    // mlx_hook(win, 2, 1L << 0, key_press, data);   // KeyPressMask
    // mlx_hook(win, 3, 1L << 1, key_release, data); // KeyReleaseMask
    // mlx_hook(win, 4, NOUSE_PRESS_MASK, mouse_press, data); // ButtonPressMask
    // mlx_hook(win, 5, MOUSE_RELEASE_MASK, mouse_release, data); // ButtonReleaseMask
    // mlx_hook(win, 6, MOUSE_MOVE_MASK, mouse_move, data);  // PointerMotionMask

    // mlx_loop(disp->mlx);
}

#include <stdlib.h>
#include <window.h>

void cleanup(t_disp *disp) {
    if (!disp)
        return;
    free(disp->mlx);
    free(disp->win);
    free(disp->img);
    free(disp);
}

int close_win(t_disp *disp) {
    cleanup(disp);
    exit(EXIT_SUCCESS);
    return (0);
}

int key_hook(int keycode, t_disp *disp) {
    if (keycode == 53 || keycode == 65307)
        return close_win(disp);
    return (0);
}

// Mouse hook
/* int	mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *p; */

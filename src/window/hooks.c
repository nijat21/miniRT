#include <stdlib.h>
#include <window.h>

void cleanup(t_disp *disp)
{
    if (!disp)
        return;
    free(disp->mlx);
    free(disp->win);
    free(disp->img);
    free(disp);
}

int close_win(void *param)
{
    t_disp *disp;

    disp = (t_disp *)param;
    cleanup(disp);
    exit(EXIT_SUCCESS);
    return (0);
}

int key_hook(int keycode, void *param)
{
    if (keycode == 53 || keycode == 65307)
        return close_win((t_disp *)param);
    return (0);
}

// Mouse hook
/* int	mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param); */
/* int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *p; */

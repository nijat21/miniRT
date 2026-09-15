#include <minirt.h>
#include <window.h>

int rgb_to_int(t_rgb rgb)
{
    return (0 << 24 | (rgb.r & 0xFF) << 16 | (rgb.g & 0xFF) << 8 | (rgb.b & 0xFF));
}

void color_px(t_disp *disp, int x, int y, t_rgb rgb)
{
    char *dst;
    int color;

    if (x < 0 || x >= disp->w || y < 0 || y >= disp->h)
        return;
    dst = disp->img->addr + (y * disp->img->line_len + x * (disp->img->bits_pp / 8));
    color = rgb_to_int(rgb);
    if (color > 0)
        printf("Color: %d\n", color);
    *(unsigned int *)dst = color;
}
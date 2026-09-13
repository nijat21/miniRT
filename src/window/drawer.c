#include <minirt.h>
#include <window.h>

void color_px(t_img *img, int x, int y, t_rgb rgb)
{
    char *dst;

    dst = img->addr + (y * img->line_len + x * (img->bits_pp / 8));
    *(unsigned int *)dst = (0 << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b);
}
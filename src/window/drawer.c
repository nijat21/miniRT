#include <minirt.h>
#include <window.h>

int rgb_to_int(t_rgb rgb)
{
    return (0 << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b);
}

void color_px(t_img *img, int x, int y, t_rgb rgb)
{
    char *dst;
    int color;

    dst = img->addr + (y * img->line_len + x * (img->bits_pp / 8));
    color = rgb_to_int(rgb);
    printf("Color: %d\n", color);
    *dst = color;
}
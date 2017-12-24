#include "bmp_draw.h"

static void color_pixel(pixel *pixel, int *color)
{
	pixel->blue = color[0];
	pixel->green = color[1];
	pixel->red = color[2];
}

void draw_line(bmp_image *bmp, int *start_pt, int *end_pt, int *color, int thickness)
{
	
}

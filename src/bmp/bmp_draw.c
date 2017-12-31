#include "bmp_draw.h"

static void color_pixel(pixel *pixel, int *color)
{
	pixel->blue = color[0];
	pixel->green = color[1];
	pixel->red = color[2];
}

void draw_line(bmp_image *bmp, point *start_pt, point *end_pt, int *color, int thickness)
{
	int x0 = start_pt->x, x1 = end_pt->x, y0 = start_pt->y, y1 = end_pt->y;
	//TODO(THICKNESS, error handling for out of bounds)
	
	//bresenhams line algorithm, top notch efficiency, si
	int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx+dy, e2;

	while(1) {
		//colors pixel at x0, y0 (image-width shift for y coord)
		color_pixel(bmp->bitmap_data + x0 + (y0 * bmp->info_header.width), color);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 > dy) { err += dy; x0 += sx; } 
		if (e2 < dx) { err += dx; y0 += sy; } 
	}
}

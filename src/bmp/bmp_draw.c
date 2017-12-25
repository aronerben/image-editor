#include "bmp_draw.h"

static void color_pixel(pixel *pixel, int *color)
{
	pixel->blue = color[0];
	pixel->green = color[1];
	pixel->red = color[2];
}

void draw_line(bmp_image *bmp, point *start_pt, point *end_pt, int *color, int thickness)
{
	//calc slope of line
	//TODO(fix uint not allowing negative slope here)
	double slope = (double)(end_pt->y - start_pt->y) / (double)(end_pt->x - start_pt->x);
	printf("\n%f",slope);

	//go along x-axis and  
	for(int i = start_pt->x, j = 0; i <= end_pt->x; i++, j++) {
		int y_change = (int)(round(j * slope) * bmp->info_header.width);
		//	color_pixel(bmp->bitmap_data + i + y_change, color);
	}
	//TODO(implement THICKNESS)
}

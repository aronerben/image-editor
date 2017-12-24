#ifndef BMP_DRAW_H
#define BMP_DRAW_H

/*
 * @brief		Sets a new color for a pixel
 * @param[in] pixel	Pixel to receive new color
 * @param[in] color	Color as int components
 */
static void color_pixel(pixel *pixel, int *color);

/*
 * @brief		Draws a line on the image between two given points
 * @param[in] bmp	Bmp struct to draw line on
 * @param[in] start_pt	Starting point for line
 * @param[in] end_pt	Ending point for line
 * @param[in] color	Line color
 * @param[in] thickness Line thickness	
 */
void draw_line(bmp_image *bmp, int *start_pt, int *end_pt, int *color, int thickness);

#endif


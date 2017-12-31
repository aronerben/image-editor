#ifndef BMP_DRAW_H
#define BMP_DRAW_H

#include "bmp_general.h"

//2d point used for drawing functions
//(0,0) is bottom-left corner
typedef struct {
	int32_t x;
	int32_t y;
} point;

/*
 * @brief			Sets a new color for a pixel
 * @param[in] pixel		Pixel to receive new color
 * @param[in] color		Color as int components
 */
static void color_pixel(pixel *pixel, int *color);
/*
 * @brief			Draws a line on the image between two given points
 * @param[in] bmp		Bmp struct to draw line in
 * @param[in] start_pt		Line starting point
 * @param[in] end_pt		Line ending point
 * @param[in] color		Line color
 * @param[in] thickness		Line thickness	
 */
void draw_line(bmp_image *bmp, point *start_pt, point *end_pt, int *color, int thickness);

/*
 * @brief			Draws a circle with a given radius and center	
 * @param[in] bmp		Bmp struct to draw circle in
 * @param[in] center_pt		Circle center
 * @param[in] radius		Circle radius
 * @param[in] color_line	Circle line color
 * @param[in] thickness		Circle line thickness
 */
void draw_circle(bmp_image *bmp, point *center_pt, int radius, int *color_line, int thickness);

/*
 * @brief			Draws a rectangle with a given top-left corner, width and height	
 * @param[in] bmp		Bmp struct to draw rectangle in
 * @param[in] start_pt		Top-left corner offset, top-left corner starting point for rectangle
 * @param[in] width		Rectangle width
 * @param[in] height		Rectangle height
 * @param[in] color_line	Rectangle line color
 * @param[in] thickness		Rectangle line thickness
 */
void draw_rectangle(bmp_image *bmp, point *start_pt, int width, int height, int *color_line, int thickness);

#endif


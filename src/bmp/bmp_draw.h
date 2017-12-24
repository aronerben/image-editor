#ifndef BMP_DRAW_H
#define BMP_DRAW_H

/*
 * @brief		Draws a line on the image between two given points
 * @param[in] bmp	Bmp struct to draw line on
 * @param[in] start_pt	Starting point for line
 * @param[in] end_pt	Ending point for line
 */
void draw_line(bmp_image *bmp, int* start_pt, int* end_pt);

#endif


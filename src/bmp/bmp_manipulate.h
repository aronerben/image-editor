#ifndef TEST_H
#define TEST_H

#include "bmp_general.h"

/*
 * @brief		Parses bmp file into structs
 * @param[in] file	File to parse
 * @param[in] bmp	Bmp struct to fill
 * @returns 		Returns integer indicating success (valid bmp) or error
 */
int parse_bmp_image(FILE *file, bmp_image *bmp);


/*
 * @brief		Mirrors the image vertically
 * @param[in] bmp	Bmp struct to mirror
 */
void mirror_vert(bmp_image *bmp);

/*
 * @brief		Mirrors the image horizontally
 * @param[in] bmp	Bmp struct to mirror
 */
void mirror_horiz(bmp_image *bmp);


/*
 * @brief		Creates a bmp image file from a bmp struct
 * @param[in] bmp	Bmp struct to create file from
 */
void create_bmp_image(bmp_image *bmp);

/*
 * @brief		Changes the brightness of the image, by increasing/decrease every pixels RGB components values
 * @param[in] bmp	Bmp struct to edit brightness
 * @param[in] amount	The amount [-255 to 255] of brightness change
 * @returns		Returns a copy of the Bmp struct, because changing brightness causes information loss
 */
bmp_image edit_brightness(bmp_image *bmp, int amount);

/*
 * @brief		Rotates an image by an angle	
 * @param[in] bmp	Bmp struct to set rotation information
 * @param[in] angle	The angle [0, 360[ by what to rotate the image
 * @returns		Returns a new Bmp struct, because rotation can cause changes in width and height of the image
 */
bmp_image rotate(bmp_image *bmp, int angle);

/*
 * @brief		Retrieves the average pixel color	
 * @param[in] bmp	Bmp struct to set rotation information
 * @returns		Returns an array size 3 with RGB of average pixel 	
 */
int* get_average_pixel(bmp_image *bmp);
#endif

#ifndef TEST_H
#define TEST_H

#include <stdint.h>

//compiler directive, saves struct in memory according to bmp standard (fileheader size 16 to 14)
//required for proper fwrite() and fread() use
#pragma pack(1)
typedef struct {
	uint16_t type;
	uint32_t bmp_size;
	uint32_t reserved;
	uint32_t data_offset;
} file_header;
#pragma pack()

#pragma pack(1)
typedef struct {
	uint32_t struct_size;
	int32_t	width;
	int32_t height;
	uint16_t planes;
	uint16_t bit_depth;
	uint32_t compression;
	uint32_t image_size;
	int32_t x_res;
	int32_t y_res;
	uint32_t amount_color_used;
	uint32_t amount_color_important;
} info_header;
#pragma pack()

//struct to contain entire image (headers + data)
typedef struct {
	file_header file_header;
	info_header info_header;
	uint8_t *bitmap_data;
} bmp_image;

//MAYBE TODO(struct for pixel)

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

/*
 * @brief		Draws a line on the image between two given points
 * @param[in] bmp	Bmp struct to draw line on
 * @param[in] start_pt	Starting point for line
 * @param[in] end_pt	Ending point for line
 */
void draw_line(bmp_image *bmp, int* start_pt, int* end_pt);

#endif

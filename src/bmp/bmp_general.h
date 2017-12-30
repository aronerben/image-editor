#ifndef BMP_GENERAL_H
#define BMP_GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//compiler directive, saves struct in memory according to bmp standard (fileheader size 16 to 14)
//required for proper fwrite() and fread() usage
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

//easy pixel representation
typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel;

//struct to contain entire image (headers + data)
//make bitmap data a single pointer, not 2D array => pointer arithmetics, but simpler
typedef struct {
	file_header file_header;
	info_header info_header;
	pixel *bitmap_data;
} bmp_image;

/*
 * @brief		Parses bmp file into structs
 * @param[in] file	File to parse
 * @param[in] bmp	Bmp struct to fill
 * @returns 		Returns integer indicating success (valid bmp) or error
 */
int parse_image(FILE *file, bmp_image *bmp);

/*
 * @brief		Creates a bmp image file from a bmp struct
 * @param[in] bmp	Bmp struct to create file from
 */
void create_image(bmp_image *bmp);

#endif

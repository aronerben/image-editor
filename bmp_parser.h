#ifndef TEST_H
#define TEST_H

typedef struct {
	uint8_t type[2];
	uint32_t bmp_size;
	uint32_t reserved;
	uint32_t data_offset;
} file_header;

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

typedef struct {
	file_header file_header;
	info_header info_header;
} full_header;

#endif

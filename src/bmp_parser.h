#ifndef TEST_H
#define TEST_H

//saves structure in memory according to bmp standard (fileheader size 16 to 14)
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

typedef struct {
	file_header file_header;
	info_header info_header;
} full_header;

#endif

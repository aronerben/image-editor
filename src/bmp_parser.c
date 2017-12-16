#include <stdio.h>
#include <stdlib.h>
#include "bmp_parser.h"

int main(int argc, char *argv[])
{
	//read file with read-only mode
	//TODO(replace hard coded with main arg, safety check main arg)
	FILE *file = fopen("resources/test.BMP", "r");
	
	//allocate enough memory for the bmp struct
	bmp_image *bmp = (bmp_image*)malloc(sizeof(bmp_image));

	//parse file buffer into struct and check if file is bmp
	int success = parse_bmp(file, bmp);
	if(!success) {
		(void)printf("Invalid format");
		(void)fclose(file);
		return EXIT_FAILURE;
	}

	(void)fclose(file);
	return EXIT_SUCCESS;
}

int parse_bmp(FILE *file, bmp_image *bmp)
{
	//read file header
	(void)fread(&(bmp->file_header), sizeof(file_header), 1, file);
	
	//read info header
	(void)fread(&(bmp->info_header), sizeof(info_header), 1, file);
	
	//allocate memory for the bmp data and read in data
	bmp->bitmap_data = (uint8_t*)malloc(bmp->info_header.image_size);
	(void)fread(bmp->bitmap_data, bmp->info_header.image_size, 1, file);
	
	//check for invalid flags
	if(bmp->file_header.type != 0x4D42 || bmp->info_header.bit_depth != 24
			|| bmp->info_header.image_size == 0) {
		return 0;
	}
	
	return 1;
}

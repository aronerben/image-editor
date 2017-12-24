#include "bmp_general.h"

#define BYTE_SIZE 1

int parse_image(FILE *file, bmp_image *bmp)
{
	//read file header
	(void)fread(&(bmp->file_header), sizeof(file_header), BYTE_SIZE, file);

	//read info header
	(void)fread(&(bmp->info_header), sizeof(info_header), BYTE_SIZE, file);

	//move pointer to start of bmp data
	(void)fseek(file, bmp->file_header.data_offset, SEEK_SET);

	//allocate memory for the bmp data and read in data
	bmp->bitmap_data = (pixel*)malloc(bmp->info_header.image_size);
	(void)fread(bmp->bitmap_data, bmp->info_header.image_size, BYTE_SIZE, file);

	//close file buffer after struct completed
	(void)fclose(file);

	//(optional for now) fix colors from BGR to RGB (swap red and blue around)
	/*
	   for(int i = 0; i < bmp->info_header.image_size / 3; i++) {
	//temp var, pointer arithmetic
	pixel *cur = bmp->bitmap_data + i;
	//swap var for red
	uint8_t temp_swap = cur->red;
	cur->red = cur->blue;
	cur->blue = temp_swap;
	}
	 */

	//check for invalid flags
	//0x4D42 is "BM", required starting string for bmp
	//if bit_depth != 24 => might use different color component order and might have additional color table
	//disallow compressed images for now
	//image_size has to be != 0 to read from it
	if(bmp->file_header.type != 0x4D42 
			|| bmp->info_header.bit_depth != 24
			|| bmp->info_header.compression != 0 
			|| bmp->info_header.image_size == 0) {
		return 0;
	}
	return 1;
}

void create_image(bmp_image *bmp)
{
	//TODO(replace hardcoded with user desired, maybe when GUI)
	//create new file
	FILE *newfile = fopen("resources/new.BMP", "w");

	//write file header
	fwrite(&(bmp->file_header), BYTE_SIZE, sizeof(file_header), newfile);

	//write info header
	fwrite(&(bmp->info_header), BYTE_SIZE, sizeof(info_header), newfile);

	//write bmp data
	fwrite(bmp->bitmap_data, BYTE_SIZE, bmp->info_header.image_size, newfile);
}



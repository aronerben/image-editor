#include <stdio.h>
#include <stdlib.h>
#include "bmp_parser.h"

int main(int argc, char *argv[])
{
	//read file with read-only mode
	//TODO(replace hard coded with main arg, maybe when GUI, safety check main arg)
	FILE *file = fopen("resources/test.BMP", "r");

	//allocate enough memory for the bmp struct
	bmp_image *bmp = (bmp_image*)malloc(sizeof(bmp_image));

	//parse file buffer into struct and check if file is bmp
	int success = parse_bmp_image(file, bmp);
	if(!success) {
		(void)printf("Invalid format");
		return EXIT_FAILURE;
	}

	//bmp edit functions
	mirror_horiz(bmp);
	mirror_vert(bmp);
	create_bmp_image(bmp);
	

	//free memory
	free(bmp->bitmap_data);
	free(bmp);	
	return EXIT_SUCCESS;
}

int parse_bmp_image(FILE *file, bmp_image *bmp)
{
	//read file header
	(void)fread(&(bmp->file_header), sizeof(file_header), 1, file);

	//read info header
	(void)fread(&(bmp->info_header), sizeof(info_header), 1, file);

	//move pointer to start of bmp data
	(void)fseek(file, bmp->file_header.data_offset, SEEK_SET);

	//allocate memory for the bmp data and read in data
	bmp->bitmap_data = (uint8_t*)malloc(bmp->info_header.image_size);
	(void)fread(bmp->bitmap_data, bmp->info_header.image_size, 1, file);

	//check for invalid flags
	if(bmp->file_header.type != 0x4D42 || bmp->info_header.bit_depth != 24
			|| bmp->info_header.image_size == 0) {
		return 0;
	}
	(void)fclose(file);
	return 1;
}

void mirror_vert(bmp_image *bmp)
{
	//setting the height to negative causes bmp to flip
	bmp->info_header.height *= -1;
}

void mirror_horiz(bmp_image *bmp)
{	
	//store image width for easier access
	int32_t image_width = bmp->info_header.width;

	//go through every image-row to the height
	for(int i = 0; i < bmp->info_header.image_size; i += image_width * 3) {
		//invert every pixel in width-array
		for(int j = 0; j <= (image_width - 1) / 2; j++) {
			//invert every RGB component when inverting pixels
			for(int k = 0; k <= 2; k++) {
				//use scaling factor of 3 for shifting between pixels
				//regular 2 way swap operation with temp var
				int temp_swap = *(bmp->bitmap_data + i + (j * 3) + k);
				*(bmp->bitmap_data + i + (j * 3) + k) = *(bmp->bitmap_data + i + ((image_width - j - 1) * 3) + k);
				*(bmp->bitmap_data + i + ((image_width - j - 1) * 3) + k) = temp_swap;
			}
		}
	}
}

void create_bmp_image(bmp_image *bmp)
{
	//TODO(replace hardcoded with user desired, maybe when GUI)
	//create new file
	FILE *newfile = fopen("resources/new.BMP", "w");

	//write file header
	fwrite(&(bmp->file_header), 1, sizeof(file_header), newfile);

	//write info header
	fwrite(&(bmp->info_header), 1, sizeof(info_header), newfile);

	//write bmp data
	fwrite(bmp->bitmap_data, 1, bmp->info_header.image_size, newfile);
}

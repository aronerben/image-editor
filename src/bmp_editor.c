#include <stdio.h>
#include <stdlib.h>
#include "bmp_editor.h"

int parse_image(FILE *file, bmp_image *bmp)
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

	//close file buffer after struct completed
	(void)fclose(file);

	//check for invalid flags
	if(bmp->file_header.type != 0x4D42 || bmp->info_header.bit_depth != 24
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
	fwrite(&(bmp->file_header), 1, sizeof(file_header), newfile);

	//write info header
	fwrite(&(bmp->info_header), 1, sizeof(info_header), newfile);

	//write bmp data
	fwrite(bmp->bitmap_data, 1, bmp->info_header.image_size, newfile);
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

	//go through every image-row up to the height
	for(int i = 0; i < bmp->info_header.image_size; i += image_width * 3) {
		//set up "mirror"-swapping in each width-array
		for(int j = 0; j <= (image_width - 1) / 2; j++) {
			//swap every RGB component of start pixel with target pixel
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

bmp_image edit_brightness(bmp_image *bmp, int amount)
{
	//create copy because changing an images brightness causes 
	//information loss and is therefore not always reversible
	bmp_image copy = *bmp;

	//go through every pixels RGB component and increase by amount, limited to max 255 and min 0
	for(int i = 0; i < copy.info_header.image_size; i++) {
		if(*(copy.bitmap_data + i) + amount > 255) {
			*(copy.bitmap_data + i) = 255; 
		} else if(*(copy.bitmap_data + i) + amount < 0) {
			*(copy.bitmap_data + i) = 0;
		} else {
			*(copy.bitmap_data + i) += amount;
		}
	}
	return copy;
}

bmp_image rotate(bmp_image *bmp, int angle)
{
	//returns completly new bmp, since rotating might change width and height
	//TODO(find middle of image, 
	//make distance corner to middle new distance from center to sides, 
	//fill canvas with 0,0,0 pixels,
	//rotate with rotation matrix,
	//check for edge smoothing)
	
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "bmp_editor.h"

#define BYTE_SIZE 1
#define COLOR_COMPONENTS 3

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

void mirror_vert(bmp_image *bmp)
{
	//setting the height to negative causes bmp to flip
	bmp->info_header.height *= -1;
}

void mirror_horiz(bmp_image *bmp)
{	
	//store image width for easier access
	int32_t image_width = bmp->info_header.width;

	//go through every pixel row through to max height	
	for(int i = 0; i < bmp->info_header.image_size / COLOR_COMPONENTS; i += image_width) {
		//swap pixels in a row by swapping the ends and moving to the middle from both sides
		for(int j = 0; j < (image_width - 1) / 2; j++) {
			//regular 2 way swap with temp variable
			pixel temp_swap = *(bmp->bitmap_data + i + j);
			*(bmp->bitmap_data + i + j) = *(bmp->bitmap_data + i + (image_width - 1 - j));
			*(bmp->bitmap_data + i + (image_width - 1 - j)) = temp_swap;
		}	
	} 
}

bmp_image edit_brightness(bmp_image *bmp, int amount)
{
	//create copy because changing an image's brightness causes 
	//information loss and is therefore not always reversible
	bmp_image copy = *bmp;

	//go through every pixels and increase by amount, limited to max 255 and min 0
	for(int i = 0; i < copy.info_header.image_size / COLOR_COMPONENTS; i++) {
		pixel *cur = copy.bitmap_data + i; 
		cur->blue = fmin(255, fmax(0, cur->blue + amount));
		cur->green = fmin(255, fmax(0, cur->green + amount));
		cur->red = fmin(255, fmax(0, cur->red + amount));
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
	return *bmp;
}

int* get_average_pixel(bmp_image *bmp)
{
	//temp array to calculate the averages with double
	double color_calc[3];
	//array to return at the end (=> dynamic memory)
	int *average_colors = (int*) malloc(sizeof(int) * 3);

	//add all pixel values (every component) together
	for(int i = 0; i < bmp->info_header.image_size / COLOR_COMPONENTS; i++) {
		pixel *cur = bmp->bitmap_data + i; 
		color_calc[0] += cur->blue; 	
		color_calc[1] += cur->green; 	
		color_calc[2] += cur->red; 	
	}

	//get averages for each component, round doubles to int
	for(int i = 0; i <= 2; i++) {
		average_colors[i] = round(color_calc[i] / (double)(bmp->info_header.image_size / 3));
	}

	return average_colors;
}

void draw_line(bmp_image *bmp, int* start_pt, int* end_pt)
{
	//TODO(make linedrawing)
}

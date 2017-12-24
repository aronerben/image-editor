#include <math.h> 
#include "bmp_manipulate.h"
#include "bmp_general.h"

#define COLOR_COMPONENTS 3

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

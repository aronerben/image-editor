#include <stdio.h>
#include <stdlib.h>
#include "bmp/bmp_general.c"
#include "bmp/bmp_manipulate.c"
#include "bmp/bmp_draw.c"

int main(int argc, char *argv[])
{
	//read file with read-only mode
	//TODO(replace hard coded with main arg, maybe when GUI, safety check main arg)
	FILE *file = fopen("resources/test.BMP", "r");

	//allocate enough memory for the bmp struct
	bmp_image *bmp = (bmp_image*)malloc(sizeof(bmp_image));

	//parse file buffer into struct and check if file is bmp
	int success = parse_image(file, bmp);
	if(!success) {
		(void)printf("Invalid format");
		return EXIT_FAILURE;
	}

	//bmp edit functions, testing out
	/*
	point start = {0, 160};
	point end = {235, 0};
	int color[3] = {255, 255, 255};
	int thickness = 1;
	(void)draw_line(bmp, &start, &end, color, thickness); 
	(void)create_image(bmp);
	*/

	//free bmp struct memory
	(void)free(bmp->bitmap_data);
	(void)free(bmp);	
	return EXIT_SUCCESS;
}

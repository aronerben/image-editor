#include <stdio.h>
#include <stdint.h>
#include "bmp_parser.h"
#pragma pack(1)

int main(int argc, char* argv[])
{	
	FILE *fp = fopen("resources/test.BMP", "r");
	full_header header;
	fread(&(header.file_header.type), 2, 1, fp);
	fseek(fp, 2, SEEK_SET);
	fread(&(header.file_header.bmp_size), 4, 1, fp);
	fseek(fp, 6, SEEK_SET);
	fread(&(header.file_header.reserved), 4, 1, fp);
	fseek(fp, 10, SEEK_SET);
	fread(&(header.file_header.data_offset), 4, 1, fp);
	(void)printf("Result: \n");
	(void)printf("%p\n", header.file_header.type);
	(void)printf("%d\n", header.file_header.bmp_size*2);
	(void)printf("%d\n", header.file_header.reserved);
	(void)printf("%d\n", header.file_header.data_offset);
	fclose(fp);
	(void)printf("%d\n", sizeof(file_header));
	(void)printf("%d\n", sizeof(info_header));
	return 0;
}

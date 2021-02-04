//********************************************************************************************
// Author: Tyler Bartlett
// Files: bitMaps.c, in.bmp, out1.bmp, out2.bmp
// Date: 03/18/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Project: 6
// Desc: 
//		
//********************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <WinBase.h>

#pragma pack(push, 1)
typedef struct Pix
{
	unsigned char B;
	unsigned char G;
	unsigned char R;
	//unsigned char A;
}Pix;
#pragma pack(pop)

#pragma pack(push, 1)

typedef struct BitMap
{
	short Signature;
	long Reserved1;
	long Reserved2;
	long DataOffSet;

	long Size;
	long Width;
	long Height;
	short Planes;
	short BitsPerPixel;
	long Compression;
	long SizeImage;
	long XPixelsPreMeter;
	long YPixelsPreMeter;
	long ColorsUsed;
	long ColorsImportant;
	struct Pix *pixels;
} BitMap;
#pragma pack(pop)

int main(int argc, char **argv)
{
	unsigned long int i = 0;//to count pixels readed
	unsigned long int S = 0;//number of pixcels to read
	
	struct BitMap source_info;//to store bitmap info header
	struct Pix source_pix;// to store pixcels

	FILE *fp;		//input bitmap
	FILE *fpOut1;	//output bitmap
	FILE *fpOut2;	//output bitmap

	if (!(fp = fopen("in.bmp", "rb")))//open in binery read mode
	{
		printf(" can not open file\n");//prind and exit if file open error
		exit(-1);
	}

	fpOut1 = fopen("out1.bmp", "wb");//opne in binery write mode
	fpOut2 = fopen("out2.bmp", "wb");

	// read header
	fread(&source_info, (sizeof(BitMap) - sizeof(struct Pix*)), 1, fp);

	// total pixels
	S = source_info.Width*source_info.Height;

	// allocate space
	Pix *pixels = (struct Pix *) malloc(sizeof(struct Pix *) * S);
	source_info.pixels = pixels;

	//read pixcels
	for (i = 1; i <= S; i++)
	{
		fread(&source_pix, sizeof(struct Pix), 1, fp);
		source_info.pixels[i - 1] = source_pix;
	}

	// write header to dest files
	fwrite(&source_info, sizeof(source_info) - 4, 1, fpOut1);
	
	//source_info.Width = source_info.Width / 2;
	//source_info.Height = source_info.Height / 2;
	//source_info.SizeImage = source_info.Width * source_info.Height;
	fwrite(&source_info, sizeof(source_info) - 4, 1, fpOut2);

	//sky colors (light blue to purple)
	Pix ogColor;
	ogColor.B = 232;
	ogColor.G = 162;
	ogColor.R = 0;
	Pix newColor;
	newColor.B = 255;
	newColor.G = 0;
	newColor.R = 255;
	//sunRGB: 255,242,0; groundRGB: 34,177,76; dudeRGB: 0,0,0; 
	Pix whitePix;
	whitePix.B = 255;
	whitePix.G = 255;
	whitePix.R = 255;

	int halfWidth = 0;
	int fullWidth = 0;
	//write pixels to files
	for (i = 0; i <= S; i++)
	{
		if ((i) >= (S / 2) && halfWidth <= source_info.Width/2)
		{
			fwrite(&source_info.pixels[i], sizeof(struct Pix), 1, fpOut2);
		}
		else
		{
			fwrite(&whitePix, sizeof(struct Pix), 1, fpOut2);
		}

		halfWidth++;
		fullWidth++;

		if (fullWidth == source_info.Width)
		{
			halfWidth = 0;
			fullWidth = 0;
		}

		if (source_info.pixels[i].B == ogColor.B && source_info.pixels[i].G == ogColor.G && source_info.pixels[i].R == ogColor.R)
		{
			source_info.pixels[i].B = newColor.B;
			source_info.pixels[i].G = newColor.G;
			source_info.pixels[i].R = newColor.R;
		}
		fwrite(&source_info.pixels[i], sizeof(struct Pix), 1, fpOut1);
	}

	//close 
	fclose(fp);
	fclose(fpOut1);
	fclose(fpOut2);

	//getchar();
	return 0;
}

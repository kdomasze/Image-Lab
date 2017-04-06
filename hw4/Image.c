#include "Image.h"
#include <stdlib.h>
#include <stdio.h>

unsigned char GetPixelR(IMAGE *image, unsigned int x, unsigned int y)
{
	int location = x + y * image->Width; /* index of the pixel */
	return image->R[location];
}

unsigned char GetPixelG(IMAGE *image, unsigned int x, unsigned int y)
{
	int location = x + y * image->Width; /* index of the pixel */
	return image->G[location];
}

unsigned char GetPixelB(IMAGE *image, unsigned int x, unsigned int y)
{
	int location = x + y * image->Width; /* index of the pixel */
	return image->B[location];
}

void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r)
{
	int location = x + y * image->Width; /* index of the pixel */
	image->R[location] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g)
{
	int location = x + y * image->Width; /* index of the pixel */
	image->G[location] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b)
{
	int location = x + y * image->Width; /* index of the pixel */
	image->B[location] = b;
}


IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *img;
	img = malloc(sizeof *img);
	img->R = malloc(sizeof(unsigned char) * (Height * Width));
	img->G = malloc(sizeof(unsigned char) * (Height * Width));
	img->B = malloc(sizeof(unsigned char) * (Height * Width));

	if (!img)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	img->Width = Width;
	img->Height = Height;

	return img;
}

void DeleteImage(IMAGE *image)
{
	free(image->R);
	free(image->G);
	free(image->B);
	free(image);
}

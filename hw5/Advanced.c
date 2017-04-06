/*********************************************************************/ 
/* Advanced.h: header file for advanced DIP operations	             */ 
/*                                                                   */
/* History:                                                          */
/* 10/29/13 Alex Chu  updated for EECS22 assignment4 Fall2013	     */
/* 10/16/11 Weiwei Chen  updated for EECS22 assignment3 FAll2012     */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 FAll2011             */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Image.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

/* Posterization */
IMAGE *Posterize(IMAGE *image, 
	   unsigned char rbits, 
	   unsigned char gbits,
	   unsigned char bbits)
{
        
        unsigned char maskzero[8]={0xff-0x1, 0xff-0x2, 0xff-0x4, 0xff-0x8, 0xff-0x10, 0xff-0x20, 0xff-0x40, 0xff-0x80};
        unsigned char maskone[8]={0x0, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f};
        int x, y;
	unsigned r, g, b;
	
	assert(image);

        for(x = 0; x < image->Width; x ++)
        {
                for(y = 0; y < image->Height; y ++)
                {
			r = GetPixelR(image, x, y);
                        r &= maskzero[rbits - 1];
                        r |= maskone[rbits - 1];
			SetPixelR(image, x, y, r);

			g = GetPixelG(image, x, y);
                        g &= maskzero[gbits - 1];
                        g |= maskone[gbits - 1];
			SetPixelG(image, x, y, g);

			b = GetPixelB(image, x, y);
                        b &= maskzero[bbits - 1];
                        b |= maskone[bbits - 1];
			SetPixelB(image, x, y, b);
                }
        }
	return image;
}

/* add noise to image */
IMAGE *AddNoise(  int n, 
		IMAGE *image)
{
	int x, y, i;
	int num; /* number of noise added */

		assert(image);

	num = ( n*image->Height*image->Width )/100;
	srand( 0 );

	for ( i = 0; i < num; i++ )
	{
		x = ( (double)rand()/RAND_MAX )*(image->Width-1);
		y = ( (double)rand()/RAND_MAX )*(image->Height-1);
		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}
	printf( "\"AddNoise\" operation is done!\n" );
	return image;
}


/* overlay with another image */
IMAGE *Overlay(   char fname[SLEN], 
		IMAGE *image,  
		unsigned int x_offset, 
		unsigned int y_offset)
{
	int x=0, y=0;

	/*  the second image */
	IMAGE	*image2 = NULL;

	/*  create the second image */
	image2 = ReadImage(fname);

	for(y = 0; y < image2->Height; y++)
	{
		for(x = 0; x < image2->Width; x++)
		{
			if(	!(GetPixelR(image2, x, y) > 250 &&
				(GetPixelG(image2, x, y) > 250) && 
				(GetPixelB(image2, x, y) > 250)) &&
				x+x_offset < image->Width && y+y_offset < image->Height)
		  	{
				SetPixelR(image, x+x_offset, y+y_offset, GetPixelR(image2, x, y));
				SetPixelG(image, x+x_offset, y+y_offset, GetPixelG(image2, x, y));
				SetPixelB(image, x+x_offset, y+y_offset, GetPixelB(image2, x, y));
			}
		}
	}

	DeleteImage(image2);
	image2 = NULL;
	return image;
}

/* Resize */
IMAGE *Resize(	unsigned int percentage, IMAGE *image)
{
	unsigned int    x, y, x1, y1, x2, y2, i, j, tmpR, tmpG, tmpB;
	unsigned int 	NEW_WIDTH, NEW_HEIGHT;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	IMAGE *image_tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	if(percentage <= 0 || percentage > 500){
		printf("Resizing percentage %d%% is out of the range, Sorry! \n", percentage);
		return image;
	}

	NEW_WIDTH = WIDTH * percentage / 100;
	NEW_HEIGHT = HEIGHT * percentage / 100;
	image_tmp = CreateImage(NEW_WIDTH, NEW_HEIGHT);
	
	for(x = 0; x < NEW_WIDTH; x ++){
		for(y = 0; y < NEW_HEIGHT; y++){
			x1 = (unsigned int)(x / (percentage / 100.00));
			y1 = (unsigned int)(y / (percentage / 100.00));
			x2 = (unsigned int)((x + 1) / (percentage / 100.00));
			y2 = (unsigned int)((y + 1) / (percentage / 100.00));
			tmpR = tmpB = tmpG = 0;
			
			if(percentage < 100){
				for(i = x1; i < x2; i ++){
					for(j = y1; j < y2; j ++){
						tmpR += GetPixelR(image, i, j);
						tmpG += GetPixelG(image, i, j);
						tmpB += GetPixelB(image, i, j);
					}
				}
				SetPixelR(image_tmp, x, y, tmpR / ((x2 - x1) * (y2 - y1)));
				SetPixelG(image_tmp, x, y, tmpG / ((x2 - x1) * (y2 - y1)));
				SetPixelB(image_tmp, x, y, tmpB / ((x2 - x1) * (y2 - y1)));

			}
			else{
				SetPixelR(image_tmp, x, y, GetPixelR(image, x1, y1));
				SetPixelG(image_tmp, x, y, GetPixelG(image, x1, y1));
				SetPixelB(image_tmp, x, y, GetPixelB(image, x1, y1));
			}
		}
	}

	DeleteImage(image);
	image = NULL;
	return image_tmp;
}

/* Rotate */
IMAGE *Rotate(IMAGE *image)
{
	int             x, y;
	unsigned int	tmp;
	unsigned int WIDTH;
	unsigned int HEIGHT;    
	IMAGE *image_tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	image_tmp = CreateImage(WIDTH, HEIGHT);

	for(x = 0; x < WIDTH; x ++){
		for(y = 0; y < HEIGHT; y++){
			SetPixelR(image_tmp, x, y, GetPixelR(image, x, y));
			SetPixelG(image_tmp, x, y, GetPixelG(image, x, y));
			SetPixelB(image_tmp, x, y, GetPixelB(image, x, y));
		}
	}

	tmp = image->Width;
	image->Width = image->Height;
	image->Height = tmp;

	for(x = 0; x < WIDTH; x ++){
		for(y = 0; y < HEIGHT; y++){
			SetPixelR(image, HEIGHT -1 - y, x, GetPixelR(image_tmp, x, y));
			SetPixelG(image, HEIGHT -1 - y, x, GetPixelG(image_tmp, x, y));
			SetPixelB(image, HEIGHT -1 - y, x, GetPixelB(image_tmp, x, y));
		}
	}

	DeleteImage(image_tmp);
	image_tmp = NULL;
	return image;
}

/* BONUS: Crop */
IMAGE *Crop(IMAGE *image, unsigned int x, unsigned int y, unsigned int W, unsigned int H)
{
	int	i, j;

	assert(image);
	if (W > image->Width) {
		W = image->Width;
	}
	if (H > image->Height) {
		H = image->Height;
	}
	if (x > image->Width-1) {
		x = image->Width-1;
	}
	if (y > image->Height-1) {
		y = image->Height-1;
	}

	IMAGE *image_tmp;
	if ( (x + W > image->Width) && (y + H < image->Height)) {
		image_tmp = CreateImage(image->Width-x, H);
	}
	else if ( (x + W < image->Width) && (y + H > image->Height)) {
		image_tmp = CreateImage(W, image->Height-y);
	}
	else if ( (x + W > image->Width) && (y + H > image->Height)) {
		image_tmp = CreateImage(image->Width-x, image->Height-y);		
	}
	else {
		image_tmp = CreateImage(W, H);
	}

	for (i = 0; i < image_tmp->Width; i++) {
		for (j = 0; j < image_tmp->Height; j++) {
				SetPixelR(image_tmp, i, j, GetPixelR(image, i+x, j+y));
				SetPixelG(image_tmp, i, j, GetPixelG(image, i+x, j+y));
				SetPixelB(image_tmp, i, j, GetPixelB(image, i+x, j+y));
		}
	}

	DeleteImage(image);
	image = NULL;
	return image_tmp;
}

/* Juliaset */
IMAGE *Juliaset(unsigned int W, unsigned int H, unsigned int max_iteration)
{
	float x0, y0, x, y, xtemp;
	float zoom = 1.0, offset_x = 0.0, offset_y = 0.0;
	unsigned int row, column;
	unsigned int iteration;
	unsigned int color;
	const unsigned char palette[MAX_COLOR][3] = {
	/* r   g   b*/
	{   0,   0,   0 },	/* 0, black 		*/
	{ 127,   0,   0 },	/* 1, brown 		*/
	{ 255,   0,   0 },	/* 2, red 		*/
	{ 255, 127,   0 },	/* 3, orange 		*/
	{ 255, 255,   0 },	/* 4, yellow 		*/
	{ 127, 255,   0 },	/* 5, light green 	*/
	{   0, 255,   0 },	/* 6, green 		*/
	{   0, 255, 127 },	/* 7, blue green 	*/
	{   0, 255, 255 },	/* 8, turquoise 	*/
	{ 127, 255, 255 },	/* 9, light blue 	*/
	{ 255, 255, 255 },	/* 10, white 		*/
	{ 255, 127, 255 },	/* 11, pink 		*/
	{ 255,   0, 255 },	/* 12, light pink 	*/
	{ 127,   0, 255 },	/* 13, purple 		*/
	{   0,   0, 255 },	/* 14, blue 		*/
	{   0,   0, 127 }	/* 15, dark blue 	*/
};	

	IMAGE *image;
	image = CreateImage(W, H);

	/* The following is taken (with very few adaptations) from:	*/
 	/* http://lodev.org/cgtutor/juliamandelbrot.html 		*/

	x0 = -0.7;
	y0 = 0.27015;

	for(row = 0; row < image->Width; row ++)
	{
		for(column = 0; column < image->Height; column ++)
		{
			x = 1.5 * (row - image->Width / 2.0) / (0.5 * zoom * image->Width) + offset_x;
			y = (column - image->Height / 2.0) / (0.5 * zoom * image->Height) + offset_y;

			for (iteration=0; iteration < max_iteration; iteration++) {
			    	xtemp = x*x - y*y + x0;
			    	y = 2*x*y + y0;
			    	x = xtemp;
				if (x*x + y*y > 2*2) {
					break;
				}
			}

  			color = iteration % 16;

			SetPixelR(image, row, column, palette[color][0]);
			SetPixelG(image, row, column, palette[color][1]);
			SetPixelB(image, row, column, palette[color][2]);
		}
	}

	return image;
}

/* Auto test*/
void AutoTest(IMAGE *image)
{
	char fname[SLEN] = "UCI_Peter";
	char sname[SLEN];

	image = ReadImage(fname);
	image = BlackNWhite(image);
	strcpy(sname, "bw");
	SaveImage(sname, image);
	printf("Black & White tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = VFlip(image);
	strcpy(sname, "vflip");
	SaveImage(sname, image);
	printf("VFlip tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = HMirror(image);
	strcpy(sname, "hmirror");
	SaveImage(sname, image);
	printf("HMirror tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = ColorFilter(image, 252, 196, 135, 20, 0.25, 0.25, 0.4);
	strcpy(sname, "colorfilter");
	SaveImage(sname, image);
	printf("Color Filter tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Sharpen(image);
	strcpy(sname, "sharpen");
	SaveImage(sname, image);
	printf("Sharpen tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Edge(image);
	strcpy(sname, "edge");
	SaveImage(sname, image);
	printf("Edge Detection tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = AddBorder (image, 128, 128, 128, 10) ; 
	strcpy(sname, "border"); 
	SaveImage(sname, image) ; 
	printf("Border tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Posterize (image, 6, 7, 8) ; 
	strcpy(sname, "poster"); 
	SaveImage(sname, image) ; 
	printf("Posterize tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = AddNoise (10, image) ; 
	strcpy(sname, "noise"); 
	SaveImage(sname, image) ; 
	printf("AddNoise tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	strcpy(sname, "halloweenBat");
	image = Overlay(sname, image, 100, 150) ; 
	strcpy(sname, "overlaybat"); 
	SaveImage(sname, image) ; 
	printf("Overlay with same image sizes tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	strcpy(sname, "turkey");
	image = Overlay(sname, image, 165, 325) ; 
	strcpy(sname, "overlayturkey"); 
	SaveImage(sname, image) ; 
	printf("Overlay with different image sizes tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Resize(175, image);	
	SaveImage("bigresize", image);
	printf("Resizing big tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Resize(60, image);	
	SaveImage("smallresize", image);
	printf("Resizing small tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Rotate(image);	
	SaveImage("rotate", image);
	printf("Rotate 90 degrees clockwise tested!\n\n");
	DeleteImage(image);

	image = Juliaset(600, 475, 256);
	SaveImage("juliaset", image);
	printf("Generate the juliaset image tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Crop(image, 293, 53, 305, 415);
	SaveImage("crop", image);
	printf("Crop tested!\n\n");
	DeleteImage(image);

}
/* EOF Advanced.c */

/***************************************************i******************/ 
/* Image.h: source code for basic image manipulations		     */
/*								     */ 
/* 11/20/13 Che-Wei Chang: Union                                     */
/* 11/07/11 Weiwei Chen: modified for EECS22 assignment5 Fall2011    */
/* 10/20/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment4 FAll2011             */
/*********************************************************************/

#include "Image.h"

/*Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetPixelR(IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(image->Color.RGB.R);
	return image->Color.RGB.R[x + y * image->Width];
}

/*Get the color intensity of the Green channel of pixel (x, y) in image */
unsigned char GetPixelG(IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(image->Color.RGB.G);
	return image->Color.RGB.G[x + y * image->Width];
}

/*Get the color intensity of the Blue channel of pixel (x, y) in image */
unsigned char GetPixelB(IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(image->Color.RGB.B);
	return image->Color.RGB.B[x + y * image->Width];
}

/*Set the color intensity of the Red channel of pixel (x, y) in image with value r*/
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
	assert(image);
	assert(image->Color.RGB.R);
	image->Color.RGB.R[x + y * image->Width] = r;
}

/*Set the color intensity of the Green channel of pixel (x, y) in image with value g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
	assert(image);
	assert(image->Color.RGB.G);
	image->Color.RGB.G[x + y * image->Width] = g;
}

/*Set the color intensity of the Blue channel of pixel (x, y) in image with value b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{	
	assert(image);
	assert(image->Color.RGB.B); 
	image->Color.RGB.B[x + y * image->Width] = b;
}

/* GetPixel / SetPixel for YUV*/

/*Get the color intensity of the Y channel of pixel (x, y) in image */
unsigned char GetPixelY(IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(image->Color.YUV.Y);
	return image->Color.YUV.Y[x + y * image->Width];
}

/*Get the color intensity of the U channel of pixel (x, y) in image */
unsigned char GetPixelU(IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(image->Color.YUV.U);
	return image->Color.YUV.U[x + y * image->Width];
}

/*Get the color intensity of the V channel of pixel (x, y) in image */
unsigned char GetPixelV(IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(image->Color.YUV.V);
	return image->Color.YUV.V[x + y * image->Width];
}

/*Set the color intensity of the Red channel of pixel (x, y) in image with value r*/
void SetPixelY(IMAGE *image, unsigned int x,  unsigned int y, unsigned char yuv_y)
{
	assert(image);
	assert(image->Color.YUV.Y);
	image->Color.YUV.Y[x + y * image->Width] = yuv_y;
}

/*Set the color intensity of the Green channel of pixel (x, y) in image with value g */
void SetPixelU(IMAGE *image, unsigned int x,  unsigned int y, unsigned char yuv_u)
{
	assert(image);
	assert(image->Color.YUV.V);
	image->Color.YUV.U[x + y * image->Width] = yuv_u;
}

/*Set the color intensity of the Blue channel of pixel (x, y) in image with value b */
void SetPixelV(IMAGE *image, unsigned int x,  unsigned int y, unsigned char yuv_v)
{	
	assert(image);
	assert(image->Color.RGB.B);
	image->Color.YUV.V[x + y * image->Width] = yuv_v;
}

/* allocate the memory spaces for the image              */
/* and the memory spaces for the color intensity values. */
/* return the pointer to the image                       */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *image;
	if(!( image = (IMAGE *)malloc(sizeof(IMAGE)))){
		return NULL;
	}
	image->Width 	= Width;
	image->Height	= Height;
	if(!(image->Color.YUV.Y = (unsigned char*)malloc(Width * Height * sizeof(unsigned char)))){
			free (image);
			return NULL;
	}
	
	if(!(image->Color.YUV.U = (unsigned char*)malloc(Width * Height * sizeof(unsigned char)))){
			free (image->Color.YUV.Y) ; 
			free (image);
			return NULL;
	}

	if(!(image->Color.YUV.V = (unsigned char*)malloc(Width * Height * sizeof(unsigned char)))){
			free (image->Color.YUV.Y) ; 
			free (image->Color.YUV.U) ; 
			free (image);
			return NULL;
	}

	assert (image->Color.RGB.R == image->Color.YUV.Y) ; 
	assert (image->Color.RGB.G == image->Color.YUV.U) ; 
	assert (image->Color.RGB.B == image->Color.YUV.V) ; 

	return image;
}

/*release the memory spaces for the pixel color intensity values */
/*release the memory spaces for the image                        */
/*set the image pointer to be NULL                               */
void DeleteImage(IMAGE *image)
{
	assert(image);
	assert(image->Color.YUV.Y);
	assert(image->Color.YUV.U);
	assert(image->Color.YUV.V);
		
	free(image->Color.YUV.Y);
	free(image->Color.YUV.U);
	free(image->Color.YUV.V);
	image->Color.YUV.Y = NULL;
	image->Color.YUV.U = NULL;
	image->Color.YUV.V = NULL;

	free(image);
}



/* EOF Image.c */

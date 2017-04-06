#include "Movie.h"
#include "ImageList.h"

/* allocate the memory space for the movie */
/* and the memory space for the frame list. */
/* return the pointer to the movie */
MOVIE *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H)
{
	MOVIE *movie;
	if(!( movie = malloc(sizeof(MOVIE)))){
		return NULL;
	}

	movie->NumFrames = nFrames;
	movie->Width 	= W;
	movie->Height	= H;

	movie->Frames = NewImageList();
	
	return movie;
}

/*release the memory space for the frames and the frame list. */
/*release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	DeleteImageList(movie->Frames);
	free(movie);	
}

static int clip(int num)
{
	if(num > 255)
	{
		return 255;
	}

	if(num < 0)
	{
		return 0;
	}

	return num;
}

/* convert a YUV image into a RGB image */
void YUV2RGBImage(IMAGE *Image)
{
	IMAGE *temp = CreateImage(Image->Width, Image->Height);
	
	int x;
	int y;

	for(y = 0; y < Image->Height; y++)
	{
		for(x = 0; x < Image->Width; x++)
		{

			int C = GetPixelY(Image, x, y) - 16;
			int D = GetPixelU(Image, x, y) - 128;
			int E = GetPixelV(Image, x, y) - 128;

			unsigned char R = clip((298 * C + 409 * E + 128) >> 8);
			
			unsigned char G = clip((298 * C - 100 * D - 208 * E + 128) >> 8);
			
			unsigned char B = clip((298 * C + 516 * D + 128) >> 8);
			
			SetPixelR(temp, x, y, R);
			SetPixelG(temp, x, y, G);
			SetPixelB(temp, x, y, B);
		}
	}

	Image = temp;
	DeleteImage(temp);
}

/* convert a RGB image into a YUV image */
void RGB2YUVImage(IMAGE *Image)
{
	IMAGE *temp = CreateImage(Image->Width, Image->Height);
	
	int x;
	int y;

	for(y = 0; y < Image->Height; y++)
	{
		for(x = 0; x < Image->Width; x++)
		{
			unsigned char Y = clip(((66 * GetPixelR(Image, x, y) + 129 * GetPixelG(Image, x, y) + 25 * GetPixelB(Image, x, y) + 128) >> 8) + 16);
			
			unsigned char U = clip(((-38 * GetPixelR(Image, x, y) - 74 * GetPixelG(Image, x, y) + 112 * GetPixelB(Image, x, y) + 128) >> 8) + 128);
			
			unsigned char V = clip(((112 * GetPixelR(Image, x, y) - 94 * GetPixelG(Image, x, y) - 18 * GetPixelB(Image, x, y) + 128) >> 8) + 128);
			
			SetPixelY(temp, x, y, Y);
			SetPixelU(temp, x, y, U);
			SetPixelV(temp, x, y, V);
		}
	}

	Image = temp;
	DeleteImage(temp);
}


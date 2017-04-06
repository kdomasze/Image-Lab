#include "Advanced.h"

IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	int i, x, y;

	for(y = 0; y < image->Height; y++)
	{
		for(x = 0; x < image->Width; x++)
		{
			/* set all of the bits from (r/g/b)bits down to 0 */
			/* because the "index" of the bits start at 0, we need to go from 0 to (r/g/b)bits - 1, so, we make to stop right before the max value in the loops */
			for(i = 0; i < rbits; i++)
			{
				SetPixelR(image, x, y, (GetPixelR(image, x, y) & ~(1 << i)));
			}
			for(i = 0; i < gbits; i++)
			{
				SetPixelG(image, x, y, (GetPixelG(image, x, y) & ~(1 << i)));
			}
			for(i = 0; i < bbits; i++)
			{
				SetPixelB(image, x, y, (GetPixelB(image, x, y) & ~(1 << i)));
			}

			/* set all the bits from (r/g/b)bits - 1 down to 1 */
			/* for the same reason above, we have to subtract one from the max value to make sure it all works correctly */
			for(i = 0; i < rbits-1; i++)
			{
				SetPixelR(image, x, y, GetPixelR(image, x, y) | (1 << i));
			}
			for(i = 0; i < gbits-1; i++)
			{
				SetPixelG(image, x, y, GetPixelG(image, x, y) | (1 << i));
			}
			for(i = 0; i < bbits-1; i++)
			{
				SetPixelB(image, x, y, GetPixelB(image, x, y) | (1 << i));
			}
		}
	}
	return image;
}

IMAGE *AddNoise( int n, IMAGE *image)
{
	srand(time(NULL)); /* initialize the random number generator with the current system time */

	int i;

	int noiseCount = n * image->Width * image->Height / 100;

	for(i = 0; i < noiseCount; i++)
	{
		int x = rand() % image->Width;
		int y = rand() % image->Height;

		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}
	return image;
}

IMAGE *Overlay(char fname[SLEN], IMAGE *image, unsigned int x_offset, unsigned int y_offset)
{

	IMAGE *tempImage = NULL;

	tempImage = ReadImage(fname);
	
	int x;
	int y;

	for(y = 0; y < tempImage->Height; y++)
	{
		for(x = 0; x < tempImage->Width; x++)
		{
			if(GetPixelR(tempImage, x, y) < 250 && GetPixelG(tempImage, x, y) < 250 && GetPixelB(tempImage, x, y) < 250)
			{
				SetPixelR(image, x + x_offset, y + y_offset, GetPixelR(tempImage, x, y));
				SetPixelG(image, x + x_offset, y + y_offset, GetPixelG(tempImage, x, y));
				SetPixelB(image, x + x_offset, y + y_offset, GetPixelB(tempImage, x, y));
			}
		}
	}

	DeleteImage(tempImage);
	
	return image;
}

/* blur the image */
IMAGE *Blur(IMAGE *image)
{
	unsigned char R_TEMP[image->Width][image->Height];
	unsigned char G_TEMP[image->Width][image->Height];
	unsigned char B_TEMP[image->Width][image->Height];
	int x;
	int y;

	/* store a temp version of the RGB values */

	for(y = 0; y < image->Height; y++)
	{
		for(x = 0; x < image->Width; x++)
		{
			R_TEMP[x][y] = GetPixelR(image, x, y);
			G_TEMP[x][y] = GetPixelG(image, x, y);
			B_TEMP[x][y] = GetPixelB(image, x, y);
		}
	}
	
	/* Store one of the RGB values for a square of 9 pixels for later */

	unsigned char A_;
	unsigned char B_;
	unsigned char C_;
	unsigned char D_;
	unsigned char E_;
	unsigned char F_;
	unsigned char G_;
	unsigned char H_;
	unsigned char I_;

	for(y = 1; y < image->Height-1; y++)
	{
		for(x = 1; x < image->Width-1; x++)
		{
			/* get each value of the R pixels in a 9 pixel grid */
			A_ = R_TEMP[x-1][y-1];
			B_ = R_TEMP[x][y-1];
			C_ = R_TEMP[x+1][y-1];
			D_ = R_TEMP[x-1][y];
			E_ = R_TEMP[x][y];
			F_ = R_TEMP[x+1][y];
			G_ = R_TEMP[x-1][y+1];
			H_ = R_TEMP[x][y+1];
			I_ = R_TEMP[x+1][y+1];
			
			SetPixelR(image, x, y, (.111 * (A_ + B_ + C_ + D_ + E_ + F_ + G_ + H_ + I_)));
			
			/* repeat of above for G values */
			A_ = G_TEMP[x-1][y-1];
			B_ = G_TEMP[x][y-1];
			C_ = G_TEMP[x+1][y-1];
			D_ = G_TEMP[x-1][y];
			E_ = G_TEMP[x][y];
			F_ = G_TEMP[x+1][y];
			G_ = G_TEMP[x-1][y+1];
			H_ = G_TEMP[x][y+1];
			I_ = G_TEMP[x+1][y+1];

			SetPixelG(image, x, y, (.111 * (A_ + B_ + C_ + D_ + E_ + F_ + G_ + H_ + I_)));

			/* repeat of above for B values */
			A_ = B_TEMP[x-1][y-1];
			B_ = B_TEMP[x][y-1];
			C_ = B_TEMP[x+1][y-1];
			D_ = B_TEMP[x-1][y];
			E_ = B_TEMP[x][y];
			F_ = B_TEMP[x+1][y];
			G_ = B_TEMP[x-1][y+1];
			H_ = B_TEMP[x][y+1];
			I_ = B_TEMP[x+1][y+1];

			SetPixelB(image, x, y, (.111 * (A_ + B_ + C_ + D_ + E_ + F_ + G_ + H_ + I_)));
		}
	}
	return image;
}

IMAGE *Resize(unsigned int percentage, IMAGE *image)
{
	if(percentage == 100)
	{
		return image;
	}

	int newWidth = image->Width * (percentage / 100.00);
	int newHeight = image->Height * (percentage / 100.00);
	
	IMAGE *newImage = CreateImage(newWidth, newHeight);
	
	int x;
	int y;

	if(percentage > 100) /* enlarge logic */
	{
		for(y = 0; y < image->Height; y++)
		{
			for(x = 0; x < image->Width; x++)
			{
				int newx = x * (percentage / 100.00);
				int newy = y * (percentage / 100.00);
			
				int scalefactor = percentage / 100.00;

				int i;

				for(i = 0; i <= scalefactor; i++)
				{
					SetPixelR(newImage, newx+i, newy, GetPixelR(image, x, y));
					SetPixelG(newImage, newx+i, newy, GetPixelG(image, x, y));
					SetPixelB(newImage, newx+i, newy, GetPixelB(image, x, y));
					
					SetPixelR(newImage, newx, newy+i, GetPixelR(image, x, y));
					SetPixelG(newImage, newx, newy+i, GetPixelG(image, x, y));
					SetPixelB(newImage, newx, newy+i, GetPixelB(image, x, y));

					SetPixelR(newImage, newx+i, newy+i, GetPixelR(image, x, y));
					SetPixelG(newImage, newx+i, newy+i, GetPixelG(image, x, y));
					SetPixelB(newImage, newx+i, newy+i, GetPixelB(image, x, y));
				}
			}
		}
	}
	else /* shrink logic */
	{
		for(y = 0; y < newHeight; y++)
		{
			for(x = 0; x < newWidth; x++)
			{	
				int xi;
				int yi;
				
				unsigned int Rvals = 0;
				unsigned int Gvals = 0;
				unsigned int Bvals = 0;

				int newx1 = (x) / (percentage / 100.00);
				int newy1 = (y) / (percentage / 100.00);

				int newx2 = (x + 1) / (percentage / 100.00);
				int newy2 = (y + 1) / (percentage / 100.00);
				
				int i = 0;

				for(yi = newy1; yi <= newy2; yi++)
				{
					for(xi = newx1; xi <= newx2; xi++)
					{
						i++;
						Rvals += GetPixelR(image, xi, yi);	
						Gvals += GetPixelG(image, xi, yi);
						Bvals += GetPixelB(image, xi, yi);	
					}
				}

				Rvals = Rvals / i;
				Gvals = Gvals / i;
				Bvals = Bvals / i;

				SetPixelR(newImage, x, y, Rvals);
				SetPixelG(newImage, x, y, Gvals);
				SetPixelB(newImage, x, y, Bvals);
			}
		}
	}
	DeleteImage(image);

	return newImage;
}

IMAGE *Rotate(IMAGE *image)
{
	unsigned char R_TEMP[image->Width][image->Height];
	unsigned char G_TEMP[image->Width][image->Height];
	unsigned char B_TEMP[image->Width][image->Height];
	int x;
	int y;
	
	int width = image->Width;
	int height = image->Height;	

	/* store a temp version of the RGB values */

	for(y = 0; y < image->Height; y++)
	{
		for(x = 0; x < image->Width; x++)
		{
			R_TEMP[x][y] = GetPixelR(image, x, y);
			G_TEMP[x][y] = GetPixelG(image, x, y);
			B_TEMP[x][y] = GetPixelB(image, x, y);
		}
	}

	DeleteImage(image);
	image = CreateImage(height, width);
	
	for(y = 0; y < image->Height; y++)
	{
		for(x = 0; x < image->Width; x++)
		{
			SetPixelR(image, x, y, R_TEMP[image->Height - y - 1][x]);
			SetPixelG(image, x, y, G_TEMP[image->Height - y - 1][x]);
			SetPixelB(image, x, y, B_TEMP[image->Height - y - 1][x]);
		}
	}	
	return image;
}

IMAGE *Juliaset(unsigned int W, unsigned int H, unsigned int max_iteration)
{
	int x;
	int y;

	float zoom = 1;
	float cRe = -0.7;
	float cIm = 0.27015;

	IMAGE *jImage = CreateImage(W, H);

	for(x = 0; x < W; x++)
	{
		for(y = 0; y < H; y++)
		{
			/* calculate the initial real and imaginary parts of z */
			/* on the pixel location, zoom, and position values */
			float newRe = 1.5 * (x - W / 2.0) / (0.5 * zoom * W);
			float newIm = (y - H / 2.0) / (0.5 * zoom * H);

			/* i will represent the number of iterations */
			int i;
			
			/* start of the iteration process */
			for(i = 0; i < max_iteration; i++)
			{
				/* remember value of previous iteration */
				float oldRe = newRe;
				float oldIm = newIm;

				/* the actual iteration, the real and imaginary parts */
				/* are calculated */
				newRe = oldRe * oldRe - oldIm * oldIm + cRe;
				newIm = 2.0 * oldRe * oldIm + cIm;

				/* if the point is outside the circle with radius 2: stop */
				if((newRe * newRe + newIm * newIm) > 4)
				{
					break;
				}
			}
			/* use color model conversion to get rainbow palette, make */
			/* brightness black if max Iterations reached */
			
			int color = i % 16;
			
			SetPixelR(jImage, x, y, palette[color-1][0]);
			SetPixelG(jImage, x, y, palette[color-1][1]);
			SetPixelB(jImage, x, y, palette[color-1][2]);
		}
	}
	return jImage;
}

IMAGE *Crop(IMAGE *image, unsigned int x, unsigned int y, unsigned int W, unsigned int H)
{
	if(H > image->Height)
	{
		H = image->Height;
	}
	
	if(W > image->Width)
	{
		W = image->Width;
	}

	unsigned char R_TEMP[image->Width][image->Height];
	unsigned char G_TEMP[image->Width][image->Height];
	unsigned char B_TEMP[image->Width][image->Height];


	int yo;
	int xo;

	/* store a temp version of the RGB values */

	for(yo = 0; yo < image->Height; yo++)
	{
		for(xo = 0; xo < image->Width; xo++)
		{
			R_TEMP[xo][yo] = GetPixelR(image, xo, yo);
			G_TEMP[xo][yo] = GetPixelG(image, xo, yo);
			B_TEMP[xo][yo] = GetPixelB(image, xo, yo);
		}
	}

	DeleteImage(image);
	image = CreateImage(W-x, H-y);

	for(yo = y; yo < H; yo++)
	{
		for(xo = x; xo < W; xo++)
		{
			SetPixelR(image, xo-x, yo-y, R_TEMP[xo][yo]);
			SetPixelG(image, xo-x, yo-y, G_TEMP[xo][yo]);
			SetPixelB(image, xo-x, yo-y, B_TEMP[xo][yo]);
		}
	}
	return image; 
}

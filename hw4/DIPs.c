#include "DIPs.h"

/* age the image to make it look like old picture */
IMAGE *Aging(IMAGE *image)
{
  int x, y;

  for( y = 0; y < image->Height; y++ )
    for( x = 0; x < image->Width; x++ ) {
      SetPixelB(image, x, y, ( GetPixelR(image, x, y)+GetPixelG(image, x, y)+GetPixelB(image, x, y))/5);
      SetPixelR(image, x, y, ((unsigned char) GetPixelB(image, x, y)*1.6));
      SetPixelG(image, x, y, ((unsigned char) GetPixelB(image, x, y)*1.6));
  }

  return image;
}


/* change color image to black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
	int x;
	int y;

	for(y = 0; y < image->Height; y++)
	{
		for(x = 0; x < image->Width; x++)
		{
			unsigned char color = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y))/3; /* get the greyscale value for the RGB atributes */
			SetPixelR(image, x, y, color);
			SetPixelG(image, x, y, color);
			SetPixelB(image, x, y, color);
		}
	}
	return image;
}

/* flip image vertically */
IMAGE *VFlip(IMAGE *image)
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


	/* apply the temp values back to the actual in reverse */
	for(y = 0; y < image->Height; y++)
	{
		for(x = 0; x < image->Width; x++)
		{
			SetPixelR(image, x, y, R_TEMP[x][image->Height-1-y]);
			SetPixelG(image, x, y, G_TEMP[x][image->Height-1-y]);
			SetPixelB(image, x, y, B_TEMP[x][image->Height-1-y]);

		}
	}
	return image;
}

/* mirror image horizontally */
IMAGE *HMirror(IMAGE *image)
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
	
	/* apply the temp values back to the actual for only half of the widt and in reverse */

	for(y = 0; y < image->Height; y++)
	{
		for(x = 0; x < image->Width/2; x++)
		{	
			SetPixelR(image, x, y, R_TEMP[image->Width-1-x][y]);
			SetPixelG(image, x, y, G_TEMP[image->Width-1-x][y]);
			SetPixelB(image, x, y, B_TEMP[image->Width-1-x][y]);

		}
	}
	return image;
}

/* color filter */
IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, double factor_r, double factor_g, double factor_b)
{
	int x;
	int y;

	for(y = 0; y < image->Height; y++)
	{
		for(x = 0; x < image->Width; x++)
		{
			/* check if we can change the value of the pixel, and change it if we can */
			if(GetPixelR(image, x, y) >= (target_r - threshold) && GetPixelR(image, x, y) <= (target_r + threshold) &&
			   GetPixelG(image, x, y) >= (target_g - threshold) && GetPixelG(image, x, y) <= (target_g + threshold) &&
			   GetPixelB(image, x, y) >= (target_b - threshold) && GetPixelB(image, x, y) <= (target_b + threshold))
			{
				SetPixelR(image, x, y, (GetPixelR(image, x, y) * factor_r));
				SetPixelG(image, x, y, (GetPixelG(image, x, y) * factor_g));
				SetPixelB(image, x, y, (GetPixelB(image, x, y) * factor_b));
			}
		}
	}
	return image;
}

/* sharpen the image */
IMAGE *Sharpen(IMAGE *image)
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
			
			/* Check if the calculation goes over 255 or under 0. If it does, apply the max or min value to that area. If not, apply the actual value. */
			if((-A_-B_-C_-D_+9*E_-F_-G_-H_-I_) > 255)
			{
				SetPixelR(image, x, y, 255);
			}
			else if((-A_-B_-C_-D_+9*E_-F_-G_-H_-I_) < 0)
			{
				SetPixelR(image, x, y, 0);
			}
			else
			{
				SetPixelR(image, x, y, (-A_-B_-C_-D_+9*E_-F_-G_-H_-I_));
			}
			
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

			if((-A_-B_-C_-D_+9*E_-F_-G_-H_-I_) > 255)
			{
				SetPixelG(image, x, y, 255);
			}
			else if((-A_-B_-C_-D_+9*E_-F_-G_-H_-I_) < 0)
			{
				SetPixelG(image, x, y, 0);
			}
			else
			{
				SetPixelG(image, x, y, (-A_-B_-C_-D_+9*E_-F_-G_-H_-I_));
			}

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


			if((-A_-B_-C_-D_+9*E_-F_-G_-H_-I_) > 255)
			{
				SetPixelB(image, x, y, 255);
			}
			else if((-A_-B_-C_-D_+9*E_-F_-G_-H_-I_) < 0)
			{
				SetPixelB(image, x, y, 0);
			}
			else
			{
				SetPixelB(image, x, y, (-A_-B_-C_-D_+9*E_-F_-G_-H_-I_));
			}
		}
	}
	return image;
}

/* edge detection */
IMAGE *Edge(IMAGE *image)
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
	
	/* same as the Sharpen function */
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
			A_ = R_TEMP[x-1][y-1];
			B_ = R_TEMP[x][y-1];
			C_ = R_TEMP[x+1][y-1];
			D_ = R_TEMP[x-1][y];
			E_ = R_TEMP[x][y];
			F_ = R_TEMP[x+1][y];
			G_ = R_TEMP[x-1][y+1];
			H_ = R_TEMP[x][y+1];
			I_ = R_TEMP[x+1][y+1];
		
			if((-A_-B_-C_-D_+8*E_-F_-G_-H_-I_) > 255)
			{
				SetPixelR(image, x, y, 255);
			}
			else if((-A_-B_-C_-D_+8*E_-F_-G_-H_-I_) < 0)
			{
				SetPixelR(image, x, y, 0);
			}
			else
			{
				SetPixelR(image, x, y, (-A_-B_-C_-D_+8*E_-F_-G_-H_-I_));
			}

			A_ = G_TEMP[x-1][y-1];
			B_ = G_TEMP[x][y-1];
			C_ = G_TEMP[x+1][y-1];
			D_ = G_TEMP[x-1][y];
			E_ = G_TEMP[x][y];
			F_ = G_TEMP[x+1][y];
			G_ = G_TEMP[x-1][y+1];
			H_ = G_TEMP[x][y+1];
			I_ = G_TEMP[x+1][y+1];

			if((-A_-B_-C_-D_+8*E_-F_-G_-H_-I_) > 255)
			{
				SetPixelG(image, x, y, 255);
			}
			else if((-A_-B_-C_-D_+8*E_-F_-G_-H_-I_) < 0)
			{
				SetPixelG(image, x, y, 0);
			}
			else
			{
				SetPixelG(image, x, y, (-A_-B_-C_-D_+8*E_-F_-G_-H_-I_));
			}

			A_ = B_TEMP[x-1][y-1];
			B_ = B_TEMP[x][y-1];
			C_ = B_TEMP[x+1][y-1];
			D_ = B_TEMP[x-1][y];
			E_ = B_TEMP[x][y];
			F_ = B_TEMP[x+1][y];
			G_ = B_TEMP[x-1][y+1];
			H_ = B_TEMP[x][y+1];
			I_ = B_TEMP[x+1][y+1];


			if((-A_-B_-C_-D_+8*E_-F_-G_-H_-I_) > 255)
			{
				SetPixelB(image, x, y, 255);
			}
			else if((-A_-B_-C_-D_+8*E_-F_-G_-H_-I_) < 0)
			{
				SetPixelB(image, x, y, 0);
			}
			else
			{
				SetPixelB(image, x, y, (-A_-B_-C_-D_+8*E_-F_-G_-H_-I_));
			}
		}
	}
	return image;
}

IMAGE *Border(IMAGE *image, int r, int g, int b, int bwidth)
{
	int x;
	int y;
	/* apply the border for the top of the image */
	for(y = 0; y < bwidth; y++)
	{
		for(x = 0; x < image->Width; x++)
		{
			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	/* apply the border for the left side of the image */
	for(y = 0; y < image->Height; y++)
	{
		for(x = 0; x < bwidth; x++)
		{
			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	/* apply the border for the right side of the image */
	for(y = 0; y < image->Height; y++)
	{
		for(x = image->Width-bwidth; x < image->Width; x++)
		{
			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	/* apply the border for the bottom of the image */
	for(y = image->Height-bwidth; y < image->Height; y++)
	{
		for(x = 0; x < image->Width; x++)
		{
			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	return image;
}

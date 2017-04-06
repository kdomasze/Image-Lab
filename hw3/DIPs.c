#include "DIPs.h"

/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
  int x, y;

  for( y = 0; y < HEIGHT; y++ )
    for( x = 0; x < WIDTH; x++ ) {
      B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
      R[x][y] = (unsigned char) (B[x][y]*1.6);
      G[x][y] = (unsigned char) (B[x][y]*1.6);
  }
}


/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int x;
	int y;

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			unsigned char color = (R[x][y] + G[x][y] + B[x][y])/3; /* get the greyscale value for the RGB atributes */
			R[x][y] = color;
			G[x][y] = color;
			B[x][y] = color;
		}
	}
}

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	unsigned char R_TEMP[WIDTH][HEIGHT];
	unsigned char G_TEMP[WIDTH][HEIGHT];
	unsigned char B_TEMP[WIDTH][HEIGHT];
	int x;
	int y;

	/* store a temp version of the RGB values */

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			R_TEMP[x][y] = R[x][y];
			G_TEMP[x][y] = G[x][y];
			B_TEMP[x][y] = B[x][y];
		}
	}


	/* apply the temp values back to the actual in reverse */
	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			R[x][y] = R_TEMP[x][HEIGHT-1-y];
			G[x][y] = G_TEMP[x][HEIGHT-1-y];
			B[x][y] = B_TEMP[x][HEIGHT-1-y];

		}
	}
}

/* mirror image horizontally */
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	unsigned char R_TEMP[WIDTH][HEIGHT];
	unsigned char G_TEMP[WIDTH][HEIGHT];
	unsigned char B_TEMP[WIDTH][HEIGHT];
	int x;
	int y;

	/* store a temp version of the RGB values */

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			R_TEMP[x][y] = R[x][y];
			G_TEMP[x][y] = G[x][y];
			B_TEMP[x][y] = B[x][y];
		}
	}
	
	/* apply the temp values back to the actual for only half of the widt and in reverse */

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH/2; x++)
		{
			R[x][y] = R_TEMP[WIDTH-1-x][y];
			G[x][y] = G_TEMP[WIDTH-1-x][y];
			B[x][y] = B_TEMP[WIDTH-1-x][y];

		}
	}

}

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int target_r, int target_g, int target_b, int threshold, double factor_r, double factor_g, double factor_b)
{
	int x;
	int y;

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			/* check if we can change the value of the pixel, and change it if we can */
			if(R[x][y] >= (target_r - threshold) && R[x][y] <= (target_r + threshold) &&
			   G[x][y] >= (target_g - threshold) && G[x][y] <= (target_g + threshold) &&
			   B[x][y] >= (target_b - threshold) && B[x][y] <= (target_b + threshold))
			{
				R[x][y] *= factor_r;
				G[x][y] *= factor_g;
				B[x][y] *= factor_b;
			}
		}
	}

}

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	unsigned char R_TEMP[WIDTH][HEIGHT];
	unsigned char G_TEMP[WIDTH][HEIGHT];
	unsigned char B_TEMP[WIDTH][HEIGHT];
	int x;
	int y;

	/* store a temp version of the RGB values */

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			R_TEMP[x][y] = R[x][y];
			G_TEMP[x][y] = G[x][y];
			B_TEMP[x][y] = B[x][y];
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

	for(y = 1; y < HEIGHT-1; y++)
	{
		for(x = 1; x < WIDTH-1; x++)
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
				R[x][y] = 255;
			}
			else if((-A_-B_-C_-D_+9*E_-F_-G_-H_-I_) < 0)
			{
				R[x][y] = 0;
			}
			else
			{
				R[x][y] = (-A_-B_-C_-D_+9*E_-F_-G_-H_-I_);
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
				G[x][y] = 255;
			}
			else if((-A_-B_-C_-D_+9*E_-F_-G_-H_-I_) < 0)
			{
				G[x][y] = 0;
			}
			else
			{
				G[x][y] = (-A_-B_-C_-D_+9*E_-F_-G_-H_-I_);
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
				B[x][y] = 255;
			}
			else if((-A_-B_-C_-D_+9*E_-F_-G_-H_-I_) < 0)
			{
				B[x][y] = 0;
			}
			else
			{
				B[x][y] = (-A_-B_-C_-D_+9*E_-F_-G_-H_-I_);
			}
		}
	}
}

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	unsigned char R_TEMP[WIDTH][HEIGHT];
	unsigned char G_TEMP[WIDTH][HEIGHT];
	unsigned char B_TEMP[WIDTH][HEIGHT];
	int x;
	int y;
	
	 /* store a temp version of the RGB values */
	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			R_TEMP[x][y] = R[x][y];
			G_TEMP[x][y] = G[x][y];
			B_TEMP[x][y] = B[x][y];
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

	for(y = 1; y < HEIGHT-1; y++)
	{
		for(x = 1; x < WIDTH-1; x++)
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
				R[x][y] = 255;
			}
			else if((-A_-B_-C_-D_+8*E_-F_-G_-H_-I_) < 0)
			{
				R[x][y] = 0;
			}
			else
			{
				R[x][y] = (-A_-B_-C_-D_+8*E_-F_-G_-H_-I_);
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
				G[x][y] = 255;
			}
			else if((-A_-B_-C_-D_+8*E_-F_-G_-H_-I_) < 0)
			{
				G[x][y] = 0;
			}
			else
			{
				G[x][y] = (-A_-B_-C_-D_+8*E_-F_-G_-H_-I_);
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
				B[x][y] = 255;
			}
			else if((-A_-B_-C_-D_+8*E_-F_-G_-H_-I_) < 0)
			{
				B[x][y] = 0;
			}
			else
			{
				B[x][y] = (-A_-B_-C_-D_+8*E_-F_-G_-H_-I_);
			}
		}
	}
}

void Border(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int r, int g, int b, int bwidth)
{
	int x;
	int y;
	/* apply the border for the top of the image */
	for(y = 0; y < bwidth; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
	/* apply the border for the left side of the image */
	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < bwidth; x++)
		{
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
	/* apply the border for the right side of the image */
	for(y = 0; y < HEIGHT; y++)
	{
		for(x = WIDTH-bwidth; x < WIDTH; x++)
		{
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
	/* apply the border for the bottom of the image */
	for(y = HEIGHT-bwidth; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
}

#include "Advanced.h"

void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	int i, x, y;

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{

			/* set all of the bits from (r/g/b)bits down to 0 */
			/* because the "index" of the bits start at 0, we need to go from 0 to (r/g/b)bits - 1, so, we make to stop right before the max value in the loops */
			for(i = 0; i < rbits; i++)
			{
				R[x][y] = (R[x][y] & ~(1 << i));
			}
			for(i = 0; i < gbits; i++)
			{
				G[x][y] = (G[x][y] & ~(1 << i));
			}
			for(i = 0; i < bbits; i++)
			{
				B[x][y] = (B[x][y] & ~(1 << i));
			}

			/* set all the bits from (r/g/b)bits - 1 down to 1 */
			/* for the same reason above, we have to subtract one from the max value to make sure it all works correctly */
			for(i = 0; i < rbits-1; i++)
			{
				R[x][y] = (R[x][y] | (1 << i));
			}
			for(i = 0; i < gbits-1; i++)
			{
				G[x][y] = (G[x][y] | (1 << i));
			}
			for(i = 0; i < bbits-1; i++)
			{
				B[x][y] = (B[x][y] | (1 << i));
			}
		}
	}
}

void AddNoise( int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	srand(time(NULL)); /* initialize the random number generator with the current system time */

	int i;

	int noiseCount = n * WIDTH * HEIGHT / 100;

	for(i = 0; i < noiseCount; i++)
	{
		int x = rand() % WIDTH;
		int y = rand() % HEIGHT;

		R[x][y] = 255;
		G[x][y] = 255;
		B[x][y] = 255;
	}

}

void Overlay(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int x_offset, unsigned int y_offset)
{

	unsigned char Rn[WIDTH][HEIGHT];
	unsigned char Gn[WIDTH][HEIGHT];
	unsigned char Bn[WIDTH][HEIGHT];

	ReadImage(fname, Rn, Gn, Bn);

	int x;
	int y;

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			
			if(Rn[x][y] < 250 && Gn[x][y] < 250 && Bn[x][y] < 250)
			{
				R[x + x_offset][y + y_offset] = Rn[x][y];
				G[x + x_offset][y + y_offset] = Gn[x][y];
				B[x + x_offset][y + y_offset] = Bn[x][y];
			}
		}
	}

}

/* blur the image */
void Blur(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
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
			
			R[x][y] = (.111 * (A_ + B_ + C_ + D_ + E_ + F_ + G_ + H_ + I_));
			
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

			G[x][y] = (.111 * (A_ + B_ + C_ + D_ + E_ + F_ + G_ + H_ + I_));

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

			B[x][y] = (.111 * (A_ + B_ + C_ + D_ + E_ + F_ + G_ + H_ + I_));
		}
	}
}

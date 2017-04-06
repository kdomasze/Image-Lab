/*********************************************************************/
/* PhotoLab.c: homework assignment #2, for EECS 22,  Fall 2013       */
/*                                                                   */
/* History:                                                          */
/* 10/03/13 Che-Wei Chang  updated for EECS22 assignment2 Fall2013   */
/* 10/02/12 Weiwei Chen  updated for EECS22 assignment2 Fall2012     */
/* 09/27/11 Weiwei Chen  updated for EECS22 assignment2 Fall2011     */
/* 11/11/04 Rainer Doemer:   update for EECS 10 formatting style     */
/* 11/10/04 Rustam Sengupta: initial template version                */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** global definitions ***/
#define WIDTH  600		/* Image width */
#define HEIGHT 475		/* image height */
#define SLEN    80		/* maximum length of file names */
/*** function declarations ***/

/* print a menu */
void PrintMenu();

/* read image from a file */
int ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* aging the image */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* mirror image horizontally */
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int target_r, int target_g, int target_b, int threshold, double factor_r, double factor_g, double factor_b) ; 

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* Add border to image */
void Border(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int r, int g, int b, int bwidth);


int main()
{
	int menuInput = 0;
	char fnameLoad[SLEN];
	char fnameSave[SLEN];
	int redComp = 0;
	int greenComp = 0;
	int blueComp = 0;
	int threshold = 0;
	double redFact = 0;
	double greenFact = 0;
	double blueFact = 0;
	int bwidth = 0;

	/*
	 * Two dimensional arrays to hold the current image data. One array
	 * for each color component
	 */
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];

	/*  Please replace the following code with proper menu  */
	/*	with function calls for DIP operations		*/
	while(menuInput != 11)
	{
		PrintMenu();
		scanf("%d", &menuInput);
		switch(menuInput)
		{
			case 1:
				printf("Enter the file name to load: ");
				scanf("%80s", fnameLoad);			
				ReadImage(fnameLoad, R, G, B);
			break;
			case 2:
				printf("Enter a name to save the file as: ");
				scanf("%80s", fnameSave);
				SaveImage(fnameSave, R, G, B);
			break;
			case 3:
				BlackNWhite(R, G, B);
				printf("Image converted to black and white!\n");
			break;
			case 4:
				VFlip(R, G, B);
				printf("Image flipped!\n");
			break;
			case 5:
				HMirror(R, G, B);
				printf("Image mirrored horizontally!\n");
			break;
			case 6:
				printf("Enter Red component for the target color: ");
				scanf("%d", &redComp);
				printf("Enter Green component for the target color: ");
				scanf("%d", &greenComp);
				printf("Enter Blue component for the target color: ");
				scanf("%d", &blueComp);
			
				printf("Enter threshold for the color difference: ");
				scanf("%d", &threshold);
				printf("Enter factor for Red component in the target color: ");
				scanf("%lf", &redFact);
				printf("Enter factor for Green component in the target color: ");
				scanf("%lf", &greenFact);
				printf("Enter factor for Blue component in the target color: "); 
				scanf("%lf", &blueFact);

				ColorFilter(R, G, B, redComp, greenComp, blueComp, threshold, redFact, greenFact, blueFact);
				printf("Color filter applied to image!\n");
			break;
			case 7:
				Sharpen(R, G, B);
				printf("Image sharpened!\n");
			break;
			case 8:
				Edge(R, G, B);
				printf("Edge detection applied to image!\n");
			break;
			case 9:
				printf("Enter the red value of the border color: ");
				scanf("%d", &redComp);
				printf("Enter the green value of the border color: ");
				scanf("%d", &greenComp);
				printf("Enter the blue value of the border color: ");
				scanf("%d", &blueComp);
				printf("Enter the border width: ");
				scanf("%d", &bwidth);
				Border(R, G, B, redComp, greenComp, blueComp, bwidth);
				printf("Border applied to image!\n");
			break;
			case 10:
				AutoTest(R, G, B);
				printf("All functions tested!\n");
			break;
			case 11:
				printf("Quiting\n");
			break;
			default:
				printf("That is not a valid option");
			break;
		}
	}
	/*  end of replacing*/

	return 0;
}

void PrintMenu()
{
	printf("--------------------------------\n 1: Load a PPM image\n 2: Save an image in PPM and JPEG format\n 3: Change a color image to Black & White\n 4: Flip an image vertically\n 5: Mirror an image horizontally\n 6: Color-Filter an image (Red, Green, or Blue)\n 7: Sharpen an image\n 8: Sketch the edge of an image\n 9: BONUS: Add Border to an image\n 10: Test all functions\n 11: Exit");
	printf("\nPlease make your choice: ");
	
}

int ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE           *File;
	char            Type[SLEN];
	int             Width, Height, MaxValue;
	int             x, y;
	char            ftype[] = ".ppm";
  	char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/

  strcpy(fname_tmp, fname);
	strcat(fname_tmp, ftype);

	File = fopen(fname_tmp, "r");
	if (!File) {
		printf("Cannot open file \"%s\" for reading!\n", fname);
		return 1;
	}
	fscanf(File, "%79s", Type);
	if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
		printf("\nUnsupported file format!\n");
		return 2;
	}
	fscanf(File, "%d", &Width);
	if (Width != WIDTH) {
		printf("\nUnsupported image width %d!\n", Width);
		return 3;
	}
	fscanf(File, "%d", &Height);
	if (Height != HEIGHT) {
		printf("\nUnsupported image height %d!\n", Height);
		return 4;
	}
	fscanf(File, "%d", &MaxValue);
	if (MaxValue != 255) {
		printf("\nUnsupported image maximum value %d!\n", MaxValue);
		return 5;
	}
	if ('\n' != fgetc(File)) {
		printf("\nCarriage return expected!\n");
		return 6;
	}
	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = fgetc(File);
			G[x][y] = fgetc(File);
			B[x][y] = fgetc(File);
		}
	if (ferror(File)) {
		printf("\nFile error while reading from file!\n");
		return 7;
	}
	printf("%s was read successfully!\n", fname_tmp);
	fclose(File);
	return 0;
}

int SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE           *File;
	int             x, y;
	char            SysCmd[SLEN * 5];

	char            ftype[] = ".ppm";
	char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
  char            fname_tmp2[SLEN];

	strcpy(fname_tmp, fname);
        strcpy(fname_tmp2, fname);
	strcat(fname_tmp2, ftype);

	File = fopen(fname_tmp2, "w");
	if (!File) {
		printf("Cannot open file \"%s\" for writing!\n", fname);
		return 1;
	}
	fprintf(File, "P6\n");
	fprintf(File, "%d %d\n", WIDTH, HEIGHT);
	fprintf(File, "255\n");

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			fputc(R[x][y], File);
			fputc(G[x][y], File);
			fputc(B[x][y], File);
		}

	if (ferror(File)) {
		printf("\nFile error while writing to file!\n");
		return 2;
	}
	fclose(File);
	printf("%s was saved successfully. \n", fname_tmp2);

	/*
	 * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
	 * and make it world readable
	 */
	sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s",
		fname_tmp2);
	if (system(SysCmd) != 0) {
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
		return 3;
	}
	printf("%s.jpg was stored for viewing. \n", fname_tmp);

	return (0);
}

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

/* auto test*/
void
AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	char fname[SLEN] = "UCI_Peter";
	char sname[SLEN];

	ReadImage(fname, R, G, B);
	Aging(R, G, B);
  	strcpy(sname, "aging");
	SaveImage(sname, R, G, B);
	printf("Aging tested!\n\n");

	/*
	
		Filling this part with the call to your DIP functions
	
	*/
	ReadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	printf("Black and white tested!\n\n");
	
	ReadImage(fname, R, G, B);
	VFlip(R, G, B);
  	strcpy(sname, "vflip");
	SaveImage(sname, R, G, B);
	printf("VFlip tested!\n\n");

	ReadImage(fname, R, G, B);
	HMirror(R, G, B);
  	strcpy(sname, "hmirror");
	SaveImage(sname, R, G, B);
	printf("HMirror tested!\n\n");

	ReadImage(fname, R, G, B);
	ColorFilter(R, G, B, 250, 196, 135, 20, 0.25, 0.25, 0.4);
  	strcpy(sname, "colorfilter");
	SaveImage(sname, R, G, B);
	printf("Color filter tested!\n\n");

	ReadImage(fname, R, G, B);
	Sharpen(R, G, B);
  	strcpy(sname, "sharpen");
	SaveImage(sname, R, G, B);
	printf("Sharpen tested!\n\n");

	ReadImage(fname, R, G, B);
	Edge(R, G, B);
  	strcpy(sname, "edge");
	SaveImage(sname, R, G, B);
	printf("Edge tested!\n\n");

	ReadImage(fname, R, G, B);
	Border(R, G, B, 128, 128, 128, 10);
  	strcpy(sname, "border");
	SaveImage(sname, R, G, B);
	printf("Border tested!\n\n");


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

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

#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

/* print a menu */
void PrintMenu();

#ifdef DEBUG
/* auto test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);
#endif

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
	int n = 0;
	int x_offset = 0;
	int y_offset = 0;

	/*
	 * Two dimensional arrays to hold the current image data. One array
	 * for each color component
	 */
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];

	/*  Please replace the following code with proper menu  */
	/*	with function calls for DIP operations		*/
	while(menuInput != 14)
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
				printf("Enter the number of posterization bits for R channel (1 to 8): ");
				scanf("%d", &redComp);
				printf("Enter the number of posterization bits for G channel (1 to 8): ");
				scanf("%d", &greenComp);
				printf("Enter the number of posterization bits for B channel (1 to 8): ");
				scanf("%d", &blueComp);

				Posterize(R, G, B, redComp, greenComp, blueComp);	
				printf("Image Posterized!\n");
			break;
			case 11:
				printf("Enter the ammount of noise to add (from 1-100):");
				scanf("%d", &n);
				AddNoise(n, R, G, B);
				printf("Noise added to the image!\n");
			break;
			case 12:
				printf("Enter the file name to load: ");
				scanf("%80s", fnameLoad);
				printf("Enter the x offset for the overlay: ");
				scanf("%d", &x_offset);
				printf("Enter the y offset for the overlay: ");
				scanf("%d", &y_offset);
				Overlay(fnameLoad, R, G, B, x_offset, y_offset);
				printf("Overlay added!\n");
			break;
			case 13:
				Blur(R, G, B);
				printf("Surprise filter added (blur)!");
			break;
			case 14:
				printf("Quiting\n");
			break;
			#ifdef DEBUG
			case 15:
				AutoTest(R, G, B);
				printf("All functions tested!\n");
			break;
			#endif
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
	printf("--------------------------------\n 1: Load a PPM image\n 2: Save an image in PPM and JPEG format\n 3: Change a color image to Black & White\n 4: Flip an image vertically\n 5: Mirror an image horizontally\n 6: Color-Filter an image (Red, Green, or Blue)\n 7: Sharpen an image\n 8: Sketch the edge of an image\n 9: BONUS: Add Border to an image\n 10: Posterize the image\n 11: Add Noise to an image\n 12: Overlay an image\n 13: Bonus, Surprise Filter (Blur) \n 14: Exit\n");
	#ifdef DEBUG
	printf(" 15: Test all Functions\n");
	#endif
	printf("Please make your choice: ");
	
}

#ifdef DEBUG
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

	ReadImage(fname, R, G, B);
	Posterize(R, G, B, 6, 7, 8);
  	strcpy(sname, "poster");
	SaveImage(sname, R, G, B);
	printf("Posterize tested!\n\n");

	ReadImage(fname, R, G, B);
	AddNoise(10, R, G, B);
  	strcpy(sname, "noise");
	SaveImage(sname, R, G, B);
	printf("AddNoise tested!\n\n");

	ReadImage(fname, R, G, B);
	Overlay("halloweenBat", R, G, B, 100, 150);
  	strcpy(sname, "overlay");
	SaveImage(sname, R, G, B);
	printf("Overlay tested!\n\n");

	ReadImage(fname, R, G, B);
	Blur(R, G, B);
  	strcpy(sname, "surprise");
	SaveImage(sname, R, G, B);
	printf("Blur tested!\n\n");

}
#endif

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
#include "Constants.h"
#include "Advanced.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Image.h"

/* print a menu */
void PrintMenu();

#ifdef DEBUG
/* auto test all functions */
void AutoTest(IMAGE *image);
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
	int percentage = 0;
	int width = 0;
	int height = 0;
	int max_iteration = 0;

	/* Stores the image data for later use  */
	IMAGE *image = NULL;

	/*  Please replace the following code with proper menu  */
	/*	with function calls for DIP operations		*/
	while(menuInput != 18)
	{
		PrintMenu();
		scanf("%d", &menuInput);
		switch(menuInput)
		{
			case 1:
				printf("Enter the file name to load: ");
				scanf("%80s", fnameLoad);			
				image = ReadImage(fnameLoad);
				if(image == NULL)
				{
					printf("Loading of image has failed.\n");
				}
				else
				{
					printf("File loaded successfully!\n");
				}
			break;
			case 2:
				printf("Enter a name to save the file as: ");
				scanf("%80s", fnameSave);
				if(SaveImage(fnameSave, image) != 0)
				{
					printf("Unable to save file.\n");
				}
				else
				{
					printf("File saved successfully!\n");
				}
			break;
			case 3:
				image = BlackNWhite(image);
				printf("Image converted to black and white!\n");
			break;
			case 4:
				image = VFlip(image);
				printf("Image flipped!\n");
			break;
			case 5:
				image = HMirror(image);
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

				image = ColorFilter(image, redComp, greenComp, blueComp, threshold, redFact, greenFact, blueFact);
				printf("Color filter applied to image!\n");
			break;
			case 7:
				image = Sharpen(image);
				printf("Image sharpened!\n");
			break;
			case 8:
				image = Edge(image);
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
				image = Border(image, redComp, greenComp, blueComp, bwidth);
				printf("Border applied to image!\n");
			break;
			case 10:
				printf("Enter the number of posterization bits for R channel (1 to 8): ");
				scanf("%d", &redComp);
				printf("Enter the number of posterization bits for G channel (1 to 8): ");
				scanf("%d", &greenComp);
				printf("Enter the number of posterization bits for B channel (1 to 8): ");
				scanf("%d", &blueComp);

				image = Posterize(image, redComp, greenComp, blueComp);	
				printf("Image Posterized!\n");
			break;
			case 11:
				printf("Enter the ammount of noise to add (from 1-100):");
				scanf("%d", &n);
				image = AddNoise(n, image);
				printf("Noise added to the image!\n");
			break;
			case 12:
				printf("Enter the file name to load: ");
				scanf("%80s", fnameLoad);
				printf("Enter the x offset for the overlay: ");
				scanf("%d", &x_offset);
				printf("Enter the y offset for the overlay: ");
				scanf("%d", &y_offset);
				image = Overlay(fnameLoad, image, x_offset, y_offset);
				printf("Overlay added!\n");
			break;
			case 13:
				image = Blur(image);
				printf("Surprise filter added (blur)!\n");
			break;
			case 14:
				printf("Enter the percentage to resize the image: ");
				scanf("%d", &percentage);
				image = Resize(percentage, image);
				printf("Image resized!\n");	
			break;
			case 15:
				image = Rotate(image);
				printf("Image rotated 90 degrees clockwise!\n");
			break;
			case 16:
				printf("Enter the width of the set: ");
				scanf("%d", &width);
				printf("Enter the height of the set: ");
				scanf("%d", &height);
				printf("Enter the max iterations of the set: ");
				scanf("%d", &max_iteration);
				image = Juliaset(width, height, max_iteration);
				printf("Julia Set generated!\n");
			break;
			case 17:
				printf("Enter the x offset: ");
				scanf("%d", &x_offset);
				printf("Enter the y offset: ");
				scanf("%d", &y_offset);
				printf("Enter the crop width: ");
				scanf("%d", &width);
				printf("Enter the crop height: ");
				scanf("%d", &height);
				image = Crop(image, x_offset, y_offset, width, height);
				printf("Image cropped!\n");
			break;
			case 18:
				printf("Quiting\n");
				if(image != NULL)
				{
					DeleteImage(image);
				}
			break;
			#ifdef DEBUG
			case 19:
				AutoTest(image);
				printf("All functions tested!\n");
			break;
			#endif
			default:
				printf("That is not a valid option\n");
			break;
		}
	}
	/*  end of replacing*/

	return 0;
}

void PrintMenu()
{
	printf("--------------------------------\n 1: Load a PPM image\n 2: Save an image in PPM and JPEG format\n 3: Change a color image to Black & White\n 4: Flip an image vertically\n 5: Mirror an image horizontally\n 6: Color-Filter an image (Red, Green, or Blue)\n 7: Sharpen an image\n 8: Sketch the edge of an image\n 9: BONUS: Add Border to an image\n 10: Posterize the image\n 11: Add Noise to an image\n 12: Overlay an image\n 13: Bonus, Surprise Filter (Blur)\n 14: Resize the image\n 15: Rotate 90 degrees clockwise\n 16: Generate the Julia set image\n 17: BONUS: Crop\n 18: Exit\n");
	#ifdef DEBUG
	printf(" 19: Test all Functions\n");
	#endif
	printf("Please make your choice: ");
	
}

#ifdef DEBUG
/* auto test*/
void AutoTest(IMAGE *image)
{
	char fname[SLEN] = "UCI_Peter";
	char sname[SLEN];

	image = ReadImage(fname);
	image = Aging(image);
  	strcpy(sname, "aging");
	SaveImage(sname, image);
	printf("Aging tested!\n\n");
	DeleteImage(image);

	/*
	
		Filling this part with the call to your DIP functions
	
	*/
	image = ReadImage(fname);
	image = BlackNWhite(image);
	strcpy(sname, "bw");
	SaveImage(sname, image);
	printf("Black and white tested!\n\n");
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
	image = ColorFilter(image, 250, 196, 135, 20, 0.25, 0.25, 0.4);
  	strcpy(sname, "colorfilter");
	SaveImage(sname, image);
	printf("Color filter tested!\n\n");
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
	printf("Edge tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Border(image, 128, 128, 128, 10);
  	strcpy(sname, "border");
	SaveImage(sname, image);
	printf("Border tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Posterize(image, 6, 7, 8);
  	strcpy(sname, "poster");
	SaveImage(sname, image);
	printf("Posterize tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = AddNoise(10, image);
  	strcpy(sname, "noise");
	SaveImage(sname, image);
	printf("AddNoise tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Overlay("halloweenBat", image, 100, 150);
  	strcpy(sname, "overlaybat");
	SaveImage(sname, image);
	printf("Overlay of same image size tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Overlay("turkey", image, 165, 325);
  	strcpy(sname, "overlayturkey");
	SaveImage(sname, image);
	printf("Overlay of different image size tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Blur(image);
  	strcpy(sname, "surprise");
	SaveImage(sname, image);
	printf("Blur tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Resize(175, image);
  	strcpy(sname, "bigresize");
	SaveImage(sname, image);
	printf("Resizing big tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Resize(50, image);
  	strcpy(sname, "smallresize");
	SaveImage(sname, image);
	printf("Resizing small tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Rotate(image);
  	strcpy(sname, "rotate");
	SaveImage(sname, image);
	printf("Rotate 90 degrees clockwise tested!\n\n");
	DeleteImage(image);

	image = Juliaset(600, 475, 256);
  	strcpy(sname, "juliaset");
	SaveImage(sname, image);
	printf("Generation of the juliaset image tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Crop(image, 293, 53, 305, 415);
  	strcpy(sname, "crop");
	SaveImage(sname, image);
	printf("crop tested!\n\n");
	DeleteImage(image);
}
#endif

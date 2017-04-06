/*********************************************************************/ 
/* Advanced.h: program file for advanced DIP operations	             */ 
/*                                                                   */
/* History:                                                          */
/* 10/29/13 Alex Chu  updated for EECS22 assignment4 Fall2013	     */
/* 10/16/11 Weiwei Chen  updated for EECS22 assignment3 FAll2012     */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 FAll2011             */
/*********************************************************************/
#ifndef ADVANCED_H
#define ADVANCED_H

#include "Constants.h"
#include "Image.h"

/* Posterization */
IMAGE *Posterize(IMAGE *image, 
	   unsigned char rbits, 
	   unsigned char gbits,
	   unsigned char bbits);

/* add noise to image */
IMAGE *AddNoise( int percentage, 
	  IMAGE *image);

/* overlay with another image */
IMAGE *Overlay(char fname[SLEN], 
	     IMAGE *image, 
	     unsigned int x_offset, unsigned int y_offset);

/* Resize */
IMAGE *Resize(	unsigned int percentage, IMAGE *image);

/* Rotate */
IMAGE *Rotate(IMAGE *image);

/* Juliaset */
IMAGE *Juliaset(unsigned int W, unsigned int H, unsigned int max_iteration);

/* BONUS: Crop */
IMAGE *Crop(IMAGE *image, unsigned int x, unsigned int y, unsigned int W, unsigned int H);

/* Test all functions */
void AutoTest(IMAGE *image);

#endif

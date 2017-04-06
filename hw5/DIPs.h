/*********************************************************************/
/* DIPs.h: homework assignment #4, for EECS 22,  Fall 2012           */
/*                                                                   */
/* History:                                                          */
/* 10/29/13 Alex Chu  updated for EECS22 assignment4 Fall2013	     */
/* 10/16/11 Weiwei Chen  updated for EECS22 assignment3 FAll2012     */
/* 10/07/11 Weiwei Chen  updated for EECS22 assignment3 FAll2011     */
/* 						 initial version     */
/*********************************************************************/
#ifndef DIPS_H
#define DIPS_H

#include "Constants.h"
#include "Image.h"

/* change color image to black & white */
IMAGE *BlackNWhite(IMAGE *image);

/* flip image vertically */
IMAGE *VFlip(IMAGE *image);

/* mirror image horizontally */
IMAGE *HMirror(IMAGE *image);

/* sharpen the image */
IMAGE *Sharpen(IMAGE *image);

/* edge detection */
IMAGE *Edge(IMAGE *image);

/* Posterization */
IMAGE *Posterize(IMAGE *image);

/* add noise to image */
IMAGE *AddNoise(IMAGE *image);

/* Resize */
IMAGE *Resize(	unsigned int percentage, IMAGE *image);

/*JuliaSet */
IMAGE *Juliaset(unsigned int W,unsigned int H, unsigned int max_iteration, long double zoom);

#endif

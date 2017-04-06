#ifndef DIPS_H
#define DIPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"
#include "FileIO.h"

/* aging the image */
IMAGE *Aging(IMAGE *image);

/* change color image to black & white */
IMAGE *BlackNWhite(IMAGE *image);

/* flip image vertically */
IMAGE *VFlip(IMAGE *image);

/* mirror image horizontally */
IMAGE *HMirror(IMAGE *image);

/* color filter */
IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, double factor_r, double factor_g, double factor_b) ; 

/* sharpen the image */
IMAGE *Sharpen(IMAGE *image);

/* edge detection */
IMAGE *Edge(IMAGE *image);

/* Add border to image */
IMAGE *Border(IMAGE *image, int r, int g, int b, int bwidth);

#endif

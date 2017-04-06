#ifndef ADVANCED_H
#define ADVANCED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "FileIO.h"
#include "DIPs.h"
#include "Constants.h"

IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits);

IMAGE *AddNoise( int n, IMAGE *image);

IMAGE *Overlay(char fname[SLEN], IMAGE *image, unsigned int x_offset, unsigned int y_offset);

IMAGE *Blur(IMAGE *image);

IMAGE *Resize(unsigned int percentage, IMAGE *image);

IMAGE *Rotate(IMAGE *image);

IMAGE *Juliaset(unsigned int W, unsigned int H, unsigned int max_iteration);

IMAGE *Crop(IMAGE *image, unsigned int x, unsigned int y, unsigned int W, unsigned int H);

#endif

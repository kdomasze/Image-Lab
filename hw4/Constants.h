/*********************************************************************/
/* PhotoLab.c: homework assignment #2, for EECS 22,  Fall 2013       */
/*********************************************************************/

#ifndef CONSTANTS_H 
#define CONSTANTS_H

/*** global definitions ***/
#define SLEN    80		/* maximum length of file names */

#define MAX_COLOR 16

static const unsigned char palette[MAX_COLOR][3] = 
{
	/* r g b */
	{ 0, 0, 0 }, /* 0, black */
	{ 127, 0, 0 }, /* 1, brown */
	{ 255, 0, 0 }, /* 2, red */
	{ 255, 127, 0 }, /* 3, orange */
	{ 255, 255, 0 }, /* 4, yellow */
	{ 127, 255, 0 }, /* 5, light green */
	{ 0, 255, 0 }, /* 6, green */
	{ 0, 255, 127 }, /* 7, blue green */
	{ 0, 255, 255 }, /* 8, turquoise */
	{ 127, 255, 255 }, /* 9, light blue */
	{ 255, 255, 255 }, /* 10, white */
	{ 255, 127, 255 }, /* 11, pink */
	{ 255, 0, 255 }, /* 12, light pink */
	{ 127, 0, 255 }, /* 13, purple */
	{ 0, 0, 255 }, /* 14, blue */
	{ 0, 0, 127 } /* 15, dark blue */
};

#endif

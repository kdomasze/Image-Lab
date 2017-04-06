#####################################################
# Makefile: Makefile for Assignment4 EECS22 Fall2012
# 10/29/13 Alex Chu: updated for EECS22 assignment4 Fall2013
# 10/17/13 Yasaman Samei: updated for HW3 EECS22 F13
# 10/16/11 Weiwei Chen: updated for EECS22 Fall2012 
# 10/10/11 Weiwei Chen: initial solution version                  
#
#####################################################

# design names
DESIGN = MovieLab MovieLabTest

#libs
LIBS   = libfilter.a libfile_DEBUG.a 

YUV	= out.yuv out1.yuv out2.yuv juliaset.yuv

CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -c
LFLAGS = -Wall
AR     = ar rc
RANLIB = ranlib

all: MovieLab

test: MovieLabTest 

#target to generate MovieLab.o
MovieLab.o: MovieLab.c
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o 

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o

#target to generate ImageList.o
ImageList.o: ImageList.h ImageList.c
	$(CC) $(CFLAGS) -c ImageList.c -o ImageList.o

#target to generate Movie.o
Movie.o: Movie.h Movie.c
	$(CC) $(CFLAGS) -c Movie.c -o Movie.o

#target to generate Image.o
Image.o: Image.h Image.c
	$(CC) $(CFLAGS) -c Image.c -o Image.o

#target to generate libfilter.a
libfilter.a: DIPs.o ImageList.o Image.o Movie.o
	$(AR) libfilter.a  DIPs.o ImageList.o Image.o Movie.o
	$(RANLIB) libfilter.a

#target to generate MovieLab
MovieLab: MovieLab.o  libfilter.a
	$(CC) $(LFLAGS) MovieLab.o -lfilter -L. -o MovieLab

#target to generate MovieLab_DEBUG.o
MovieLab_DEBUG.o: MovieLab.c
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab_DEBUG.o 

#target to generate DIPs_DEBUG..o
DIPs_DEBUG.o: DIPs.h DIPs.c
	$(CC) $(CFLAGS) $(DEBUG) DIPs.c -o DIPs_DEBUG.o

#target to generate Movie_DEBUG..o
Movie_DEBUG.o: Movie.h Movie.c
	$(CC) $(CFLAGS) $(DEBUG) -c Movie.c -o Movie_DEBUG.o

#target to generate ImageList_DEBUG..o
ImageList_DEBUG.o: ImageList.h ImageList.c
	$(CC) $(CFLAGS) $(DEBUG) -c ImageList.c -o ImageList_DEBUG.o

#target to generate Image_DEBUG..o
Image_DEBUG.o: Image.h Image.c
	$(CC) $(CFLAGS) $(DEBUG) -c Image.c -o Image_DEBUG.o

#target to generate libfilter_DEBUG..a
libfilter_DEBUG.a: DIPs_DEBUG.o ImageList_DEBUG.o Image_DEBUG.o Movie_DEBUG.o
	$(AR) libfilter_DEBUG.a  DIPs_DEBUG.o ImageList_DEBUG.o Image_DEBUG.o Movie_DEBUG.o
	$(RANLIB) libfilter_DEBUG.a

#target to generate MovieLabTest
MovieLabTest: MovieLab_DEBUG.o  libfilter_DEBUG.a
	$(CC) $(LFLAGS) $(DEBUG) MovieLab_DEBUG.o -lfilter_DEBUG -L. -o MovieLabTest

#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(YUV) $(LIBS)
    

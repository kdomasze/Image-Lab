DEBUG = -DNDEBUG

CFLAGS = -Wall -ansi $(DEBUG)
LFLAGS = -Wall
AR = ar rc
RANLIB = ranlib
PhotoLabTest: DEBUG = -g -DDEBUG

all: PhotoLab PhotoLabTest

PhotoLab: PhotoLab.o libfileIO.a libfilter.a libimage.a
	gcc $(LFLAGS) PhotoLab.o -lfileIO -lfilter -limage -L. -o PhotoLab3

FileIO.o: FileIO.c FileIO.h
	gcc $(CFLAGS) -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h
	gcc $(CFLAGS) -c DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h
	gcc $(CFLAGS) -c Advanced.c -o Advanced.o

PhotoLab.o: PhotoLab.c
	gcc $(CFLAGS) -c PhotoLab.c -o PhotoLab.o

Image.o: Image.c Image.h
	gcc $(CFLAGS) -c Image.c -o Image.o

libfileIO.a: FileIO.o
	$(AR) libfileIO.a FileIO.o
	$(RANLIB) libfileIO.a

libfilter.a: DIPs.o Advanced.o
	$(AR) libfilter.a Advanced.o DIPs.o
	$(RANLIB) libfilter.a

libimage.a: Image.o
	$(AR) libimage.a Image.o
	$(RANLIB) libimage.a

clean:
	rm -f *.o
	rm -f *.a
	rm -f bw.ppm negative.ppm hflip.ppm hmirror.ppm vflip.ppm vmirror.ppm aging.ppm blur.ppm edge.ppm sharpen.ppm border.ppm colorfilter.ppm noise.ppm overlaybat.ppm poster.ppm overlayturkey.ppm surprise.ppm bigresize.ppm smallresize.ppm rotate.ppm juliaset.ppm crop.ppm
	rm -f PhotoLab3

FileIO_DEBUG.o: FileIO.c FileIO.h
	gcc $(CFLAGS) -c FileIO.c -o FileIO_DEBUG.o

DIPs_DEBUG.o: DIPs.c DIPs.h
	gcc $(CFLAGS) -c DIPs.c -o DIPs_DEBUG.o

Advanced_DEBUG.o: Advanced.c Advanced.h
	gcc $(CFLAGS) -c Advanced.c -o Advanced_DEBUG.o

PhotoLab_DEBUG.o: PhotoLab.c
	gcc $(CFLAGS) -c PhotoLab.c -o PhotoLab_DEBUG.o

Image_DEBUG.o: Image.c Image.h
	gcc $(CFLAGS) -c Image.c -o Image_DEBUG.o

PhotoLabTest: PhotoLab_DEBUG.o Image_DEBUG.o Advanced_DEBUG.o DIPs_DEBUG.o FileIO_DEBUG.o
	gcc $(LFLAGS) PhotoLab_DEBUG.o FileIO_DEBUG.o DIPs_DEBUG.o Advanced_DEBUG.o Image_DEBUG.o -o PhotoLabTest
	./PhotoLabTest

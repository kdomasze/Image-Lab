DEBUG = -DNDEBUG

CFLAGS = -Wall -ansi $(DEBUG)

PhotoLabTest: DEBUG = -g -DDEBUG

all: PhotoLab

PhotoLab: FileIO.o DIPs.o Advanced.o PhotoLab.o
	gcc $(CFLAGS) FileIO.o DIPs.o Advanced.o PhotoLab.o -o PhotoLab2

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc $(CFLAGS) -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc $(CFLAGS) -c DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc $(CFLAGS) -c Advanced.c -o Advanced.o

PhotoLab.o: PhotoLab.c Constants.h
	gcc $(CFLAGS) -c PhotoLab.c -o PhotoLab.o

clean:
	rm -f *.o
	rm -f PhotoLab2

PhotoLabTest: PhotoLab 
	./PhotoLab2

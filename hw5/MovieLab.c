/*********************************************************************/
/* MovieLab.c: homework assignment #5, for EECS 22,	Fall 2011			 */
/*																																	 */
/* History:																													*/
/* 10/30/11 Weiwei Chen	updated for EECS22 assignment5 FAll2011		 */
/* 10/30/11 Weiwei Chen	: initial template version									 */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/* #include <math.h> */
#include "ImageList.h"
#include "DIPs.h"
#include "Movie.h"
#include "Image.h"

/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/*read one frame from the movie */
IMAGE* ReadOneFrame(const char* fname, int nFrame, unsigned int W, unsigned H);

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie);

/* Print the command line parameter usage of the program*/
void PrintUsage();

/* type define the function pointer to the DIP function	*/
typedef IMAGE *MOP_F(IMAGE *image);

/* the function for perform DIP operations on the movie*/
void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP);

/* Fill the Juliaset images as the frames to a movie in MovieLab.c */
int JuliaSetMovie(int nFrame, unsigned int W, unsigned int H, MOVIE *movie);

int main(int argc, char *argv[])
{
	int x = 0;
	int fNum = 0;
	int fNum2 = 0;
	int mWidth = 0;
	int mHeight = 0;
	
	int sFrame = 0;
	int eFrame = 0;

	const char  *commands[13];

	int juliasetRun = 0;

	int cCount = 0;	

	int fFactor = 0;
	int rFactor = 0;
	char *fin = NULL, *fout = NULL;
	MOVIE *m = NULL;

	char *fin2 = NULL, *fout2 = NULL;
	MOVIE *m2 = NULL;
 /*entering while loop to check options entered*/
	while(x < argc)
	{
		/*specify input video*/
		if(0 == strcmp(&argv[x][0], "-i")) 
		{
			if(x < argc - 1)
			{
				fin = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fin, argv[x + 1]);
				strcat( fin, ".yuv");
			}/*fi*/
			else
			{
				printf("Missing argument for input name!");
				free(fin);
				free(fout);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/

		/*specify output video*/
		if(0 == strcmp(&argv[x][0], "-o")) 
		{
			if(x < argc - 1)
			{
				fout = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fout, argv[x + 1]);
				strcat( fout, ".yuv");
			}/*fi*/
			else
			{
				printf("Missing argument for output name!");
				free(fin);
				free(fout);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/

		/*specify concatination video*/
		if(0 == strcmp(&argv[x][0], "-cat")) 
		{
			if(x < argc - 1)
			{
				fin2 = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fin2, argv[x + 1]);
				strcat( fin2, ".yuv");
			}/*fi*/
			else
			{
				printf("Missing argument for concatination name!");
				free(fin);
				free(fout);
				free(fin2);
				free(fout2);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/

		/* Concatination frame Number */
		if(0 == strcmp(&argv[x][0], "-fcat"))
		{
			if(x < argc - 1)
			{
				fNum2 = atoi(argv[x + 1]);
			
				commands[cCount] = "cat";
				cCount++;

			}/*fi*/
			else
			{
				printf("Missing argument for number of frames for concatination!");
				free(fin);
				free(fout);
	
				free(fin2);
				free(fout2);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}

		
		/* Frame Number */
		if(0 == strcmp(&argv[x][0], "-f"))
		{
			if(x < argc - 1)
			{
				fNum = atoi(argv[x + 1]);
			}/*fi*/
			else
			{
				printf("Missing argument for number of frames!");
				free(fin);
				free(fout);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}

		/* resolution */
		if(0 == strcmp(&argv[x][0], "-s"))
		{
			if(x < argc - 1)
			{
				mWidth = atoi(strtok(argv[x + 1], "x"));
				mHeight = atoi(strtok(NULL, "x"));
			}
			else
			{
				printf("Missing argument for resolution!");
				free(fin);
				free(fout);
				return 5;
			}
			x += 2;
			continue;
		}

		/* juliusset */
		if(0 == strcmp(&argv[x][0], "-j"))
		{
			fin = (char *)malloc(sizeof(char) * (strlen("j")  + 1)); 
			commands[cCount] = "j";
			cCount++;
			x++;
			continue;
		}

		/* bw */
		if(0 == strcmp(&argv[x][0], "-bw"))
		{
			commands[cCount] = "bw";
			cCount++;
			x++;
			continue;
		}

		/* vflip */
		if(0 == strcmp(&argv[x][0], "-vflip"))
		{
			commands[cCount] = "vflip";
			cCount++;
			x++;
			continue;
		}

		/* hmirror */
		if(0 == strcmp(&argv[x][0], "-hmirror"))
		{
			commands[cCount] = "hmirror";
			cCount++;
			x++;
			continue;
		}

		/* noise */
		if(0 == strcmp(&argv[x][0], "-noise"))
		{
			commands[cCount] = "noise";
			cCount++;
			x++;
			continue;
		}

		/* edge */
		if(0 == strcmp(&argv[x][0], "-edge"))
		{
			commands[cCount] = "edge";
			cCount++;
			x++;
			continue;
		}

		/* sharpen */
		if(0 == strcmp(&argv[x][0], "-sharpen"))
		{
			commands[cCount] = "sharpen";
			cCount++;
			x++;
			continue;
		}

		/* posterize */
		if(0 == strcmp(&argv[x][0], "-poster"))
		{
			commands[cCount] = "poster";
			cCount++;
			x++;
			continue;
		}

		/* reverse */
		if(0 == strcmp(&argv[x][0], "-rvs"))
		{
			commands[cCount] = "rvs";
			cCount++;
			x++;
			continue;
		}

		/* fast foward */
		if(0 == strcmp(&argv[x][0], "-fast"))
		{
			if(x < argc - 1)
			{
				commands[cCount] = "fast";
				cCount++;
				fFactor = atoi(argv[x + 1]);
			}
			else
			{
				printf("Missing argument for fast forward!");
				free(fin);
				free(fout);
				return 5;
			}
			x += 2;
			continue;
		}

		/* resize */
		if(0 == strcmp(&argv[x][0], "-resize"))
		{
			if(x < argc - 1)
			{
				commands[cCount] = "resize";
				cCount++;
				rFactor = atoi(argv[x + 1]);
			}
			else
			{
				printf("Missing argument for resize!");
				free(fin);
				free(fout);
				return 5;
			}
			x += 2;
			continue;
		}

		/* Cut */
		if(0 == strcmp(&argv[x][0], "-cut"))
		{
			if(x < argc - 1)
			{
				sFrame = atoi(strtok(argv[x + 1], "-"));
				eFrame = atoi(strtok(NULL, "-"));

				commands[cCount] = "cut";
				cCount++;

			}
			else
			{
				printf("Missing argument for Cut!");
				free(fin);
				free(fout);
				return 5;
			}
			x += 2;
			continue;
		}

		/*help option*/
		if(0 == strcmp(&argv[x][0], "-h")) 
		{ 
			PrintUsage();
			free(fin);
			free(fout);
			return 0;
		}/*fi*/
		x++;
	}/*elihw*/

	if(!fin)
	{
		printf("Missing argument for input name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}

	if(!fout){
		printf("Missing argument for output name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}

	int i;

	for(i = 0; i < cCount; i++)
	{	
		if(0 == strcmp(commands[i], "j"))
		{
			juliasetRun = 1;
			break;
		}
	}

	m = CreateMovie(fNum, mWidth, mHeight);

	if(!juliasetRun)
	{
		ReadMovie(fin, fNum, mWidth, mHeight, m);
	}

	for(i = 0; i < cCount; i++)
	{
		if(0 == strcmp(commands[i], "rvs"))
		{
			ReverseImageList(m->Frames);
			printf("Reverse operation completed!\n");
		}

		if(0 == strcmp(commands[i], "fast"))
		{
			fNum = FastImageList(m->Frames, fFactor);
			printf("Fast forward operation completed!\n");
		}

		if(0 == strcmp(commands[i], "resize"))
		{
			ResizeImageList(m->Frames, rFactor);
			m->Width = mWidth = m->Width * (rFactor/100.00);
			m->Height = mHeight = m->Height * (rFactor/100.00);
			printf("Resize operation completed!\n");
		}
		if(0 == strcmp(commands[i], "cut"))
		{
			CropImageList(m->Frames, sFrame, eFrame);
			m->NumFrames = eFrame - (sFrame-1);
			printf("Cut operation completed!\n");
		}
		if(0 == strcmp(commands[i], "cat"))
		{
			m2 = CreateMovie(fNum2, mWidth, mHeight);
			ReadMovie(fin, fNum2, mWidth, mHeight, m2);
			ConcationateLists(m->Frames, m2->Frames);
			m->NumFrames += fNum2;
			m->Frames->Length += fNum2;
			printf("Cacatination operation completed!\n");
		}
		if(0 == strcmp(commands[i], "j"))
		{
			JuliaSetMovie(fNum, mWidth, mHeight, m);
			printf("JuliaSet operation completed!\n");
		}	
		if(0 == strcmp(commands[i], "bw"))
		{
			Movie_DIP_Operation(m, BlackNWhite);
			printf("Black/White operation completed!\n");
		}	
		if(0 == strcmp(commands[i], "vflip"))
		{
			Movie_DIP_Operation(m, VFlip);
			printf("VFlip operation completed!\n");
		}
		if(0 == strcmp(commands[i], "hmirror"))
		{
			Movie_DIP_Operation(m, HMirror);
			printf("HMirror operation completed!\n");
		}
		if(0 == strcmp(commands[i], "noise"))
		{
			Movie_DIP_Operation(m, AddNoise);
			printf("Noise operation completed!\n");
		}
		if(0 == strcmp(commands[i], "edge"))
		{
			Movie_DIP_Operation(m, Edge);
			printf("Edge operation completed!\n");
		}
		if(0 == strcmp(commands[i], "sharpen"))
		{
			Movie_DIP_Operation(m, Sharpen);
			printf("Sharpen operation completed!\n");
		}
		if(0 == strcmp(commands[i], "poster"))
		{
			Movie_DIP_Operation(m, Posterize);
			printf("Posterize operation completed!\n");
		}

	}


	SaveMovie(fout, m);

	
	DeleteMovie(m);
	free(fin);
	free(fout);
	fin = NULL;
	fout = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nFormat on command line is:\n"
	"MovieLab [option]\n"
	"-i [file_name]    to provide the input file name\n"
	"-o [file_name]    to provide the	output file name\n"
	"-f [no_frames]    to determine how many frames desired in the input stream\n"
	"-s [WidthxHeight] to set resolution of the input stream (widthxheight)\n"
	"-j                to generate the movie with JuliaSet sequences\n"
	"-bw               to activate the conversion to black and white\n"
	"-vflip            to activate vertical flip\n"
	"-hmirror          to activate horizontal flip\n"
	"-noise            to add noise to the movie \n"
  "-edge             to activate edge filter\n"
  "-sharpen          to activate sharpen filter\n"
  "-poster           to activate posterize filter\n"
  "-cat [file_name]  to provide the file to concatenate with the input file\n"  
  "-fcat [no_frames] to determine how many frames desired in the stream to be concatenated\n"  
  "-cut [Start-End]  to crop the frame from the video from frame Start to frame End\n"  
  "-resize [factor]  to resize the video with the provided factor [1-100]\n"
  "-fast   [factor]  to fast forward the video with the provided factor [1+]\n"
	"-rvs              to reverse the frame order of the input stream\n"
	"-h                to show this usage information\n"
	);
}

IMAGE* ReadOneFrame(const char *fname, int nFrame, unsigned int W, unsigned H)
{
        /*defining local variables*/
        FILE *file;

        unsigned int x, y;
        unsigned char ch;
        IMAGE* image ;

        /*checking error*/
        assert(fname);
        assert(nFrame >= 0);

        image = CreateImage(W, H) ;
        assert(image) ;

        /*opening file stream*/
        file = fopen(fname, "r");
        assert(file) ;

        /*find desired frame*/
        fseek(file, 1.5 * nFrame * W * H, SEEK_SET);

        for(y = 0; y < H; y ++){
                for(x = 0; x < W; x ++){
                        ch = fgetc(file);
                        SetPixelY(image, x, y, ch);
                }/*rof*/
        }

        for(y = 0; y < H ; y += 2){
                for(x = 0; x < W ; x += 2){
                        ch = fgetc(file);
                        SetPixelU(image, x, y, ch);
                        SetPixelU(image, x + 1, y, ch);
                        SetPixelU(image, x, y + 1, ch);
                        SetPixelU(image, x + 1, y + 1, ch);
                }
        }

        for(y = 0; y < H ; y += 2){
                for(x = 0; x < W ; x += 2){
                        ch = fgetc(file);
                        SetPixelV(image, x, y, ch);
                        SetPixelV(image, x + 1, y, ch);
                        SetPixelV(image, x, y + 1, ch);
                        SetPixelV(image, x + 1, y + 1, ch);
                }
        }

        /*checking for error*/

        assert(ferror(file) == 0) ;

        /*closing stream and terminating*/
        fclose(file);
        file = NULL;
        return image;
}


/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int i ; 
	int x, y;
	FILE *file;
	IENTRY *currFrame;

	 /*opening file stream*/
	 if(!(file = fopen(fname, "w"))){
			return 1;
	 }
	 
	 i = 0 ; 
	 printf("start savemovie, total frame %d\n", movie->NumFrames) ; 
	 currFrame = movie->Frames->First;
	 while(currFrame){
		for(y = 0; y < movie->Height; y ++){ 
			for(x = 0; x < movie->Width; x ++){
				fputc(GetPixelY(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelU(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelV(currFrame->Image, x, y), file);
			}
		}
		currFrame = currFrame->Next;	
		i++ ; 
	 }

	 fclose(file);
	 file = NULL;

	 printf("The movie file %s has been written successfully! \n", fname);
	 printf("%d frames are written to the file %s in total \n", i, fname); 
	 return 0;
}

/* read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned int H, MOVIE *movie)
{
	int i;

	for(i = 0; i < nFrame; i++)
	{
		AppendImage(movie->Frames, ReadOneFrame(fname, i, W, H));
	}

	return 1;
}

void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP)
{
	assert(movie);
	IENTRY *e = movie->Frames->First;

	while(e != NULL)
	{
		YUV2RGBImage(e->Image);
		e->Image = MovieOP(e->Image);
		RGB2YUVImage(e->Image);
		e = e->Next;
	}
}

/*Fill the Juliaset images as the frames to a movie in MovieLab.c*/
int JuliaSetMovie(int nFrame, /*number of frames in the movie */
		  unsigned int W, /*the width of the movie*/
		  unsigned int H, /*the height of the movie*/
		  MOVIE *movie /*the pointer to the output movie*/
		 )
{
	int i;

	for(i = 0; i < nFrame; i++)
	{
		AppendImage(movie->Frames, Juliaset(W, H, 512, i + .17));
		printf("Creating JuliaSet Frame #%d\n", i+1);
	}

	IENTRY *e = movie->Frames->First;
	while(e != NULL)
	{
		RGB2YUVImage(e->Image);
		e = e->Next;
	}

	return 0;
}

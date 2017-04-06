#include "ImageList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DIPs.h"
#include "Movie.h"

/* delete an image entry */
static void DeleteImageEntry(IENTRY *delete)
{
	assert(delete);
	/* check if we are not at the end of the list */
	if(delete->Next != NULL)
	{
		delete->Next->Prev = delete->Prev;
	}

	/* check if we are not at the beginning of the list */
	if(delete->Prev != NULL)
	{
		delete->Prev->Next = delete->Next;
	}

	/* free the memory for the image  */
	DeleteImage(delete->Image);
}

static IENTRY *CreateImageEntry(IMAGE *image)
{
	IENTRY *e;
	e = malloc(sizeof(IENTRY));

	if(! e)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}

	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	e->Image = image;
	
	return e;
}

/* allocate a new image list */
ILIST *NewImageList(void)
{
	ILIST *l;
	l = malloc(sizeof(ILIST));
	if(!l)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	
	l->Length = 0;
	l->First = NULL;
	l->Last = NULL;

	return l;
}

/* delete a image list (and all entries) */
void DeleteImageList(ILIST *l)
{
	IENTRY *e, *n;

	assert(l);

	e = l->First;
	while(e != NULL)
	{
		n = e->Next;

		DeleteImage(e->Image);
		free(e);

		e = n;
	}

	free(l);
}

/* insert a frame into a list at the end */
void AppendImage(ILIST *l, IMAGE *image)
{
	IENTRY *e = NULL;
	assert(l);
	assert(image);

	e = CreateImageEntry(image);

	if(l->Last)
	{
		e->List = l;
		e->Next = NULL;
		e->Prev = l->Last;
		l->Last->Next = e;
		l->Last = e;
	}
	else
	{
		e->List = l;
		e->Next = NULL;
		e->Prev = NULL;
		l->First = e;
		l->Last = e;	
	}

	l->Length++;
}

static void RemoveLast(ILIST *l)
{
	assert(l);

	l->Last = l->Last->Prev;

	l->Last->Next = NULL;
	
	l->Length--;
}

static void RemoveFirst(ILIST *l)
{
	assert(l);
	
	l->First = l->First->Next;

	l->First->Prev = NULL;
	
	l->Length--;
}

/* reverse an image list */
void ReverseImageList(ILIST *l)
{
	
	assert(l);

	IENTRY *temp = NULL;
	IENTRY *current = l->First;

	/* reverse list */
	while (current != NULL)
	{
		temp = current->Next;
		current->Next = current->Prev;
		current->Prev = temp;
		if(temp == NULL)
		{
			l->Last = l->First;
			l->First = current;
		}
		
		current = current->Prev;
	}
}

/* Crop frames from the list starting from SFrame to EFrame */
void CropImageList(ILIST *l, unsigned int SFrame, unsigned int EFrame)
{
	int i;
	int length = l->Length;
	/* remove frames before SFrame */
	for(i = 0; i < SFrame-1; i++)
	{
		RemoveFirst(l);
	}

	/* remove frames after EFrame */
	for(i = EFrame; i < length; i++)
	{
		RemoveLast(l);
	}
}

/* Resize the images in the list */
void ResizeImageList(ILIST *l, unsigned int percentage)
{
	assert(l);
	
	IENTRY *e = l->First;
	while(e != NULL)
	{
		YUV2RGBImage(e->Image);
		Resize(percentage, e->Image);
		RGB2YUVImage(e->Image);	
		e = e->Next;
	}
	assert(e == l->Last->Next);
}

/* Fast forward the video */
unsigned int FastImageList(ILIST *l, unsigned int ff_factor)
{
	assert(l);
	
	IENTRY *e = l->First;
	IENTRY *temp = NULL;

	int i;
	int count = l->Length;
	for(i = 0; i < l->Length; i++)
	{
		if(i % ff_factor != 0)
		{
			temp = e;
			DeleteImageEntry(e);
			count--;
			e = temp->Next;
		}
		else
		{
			e = e->Next;
		}
	}
	return count;
}

void ConcationateLists(ILIST *l1, ILIST *l2)
{
	assert(l1);
	assert(l2);
	IENTRY *e = l2->First;
	while(e != NULL)
	{
		AppendImage(l1, e->Image);
		e = e->Next;
	}
}


#include"stackGeneric.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

/*Function to initialize a new stack
As we are dealing with generic datatype, we need information about the size of the
element that is to be stored in stack*/
void newStack(stack *s, int elemSize, void (*freefn)(void *))
{
	s->elemSize = elemSize;
	assert(s->elemSize > 0);
	//Current allocated length is 1
	s->alloclen = 1;
	s->logiclen = 0;
	//Allocate required number of bytes
	s->elems = malloc(s->alloclen * elemSize);
	assert(s->elems != NULL);
	/*freefn is a pointer to a function which can free allocated space, in case
	of basic data tyes we pass NULL*/
	s->freefn = freefn;
}

/*Frees the space allocated to elems*/
void disposeStack(stack *s)
{
	/*Checks if the elements stored in stack are of basic types
	if not then it calls the helper function to free the allocated space*/
	if (s->freefn != NULL) {
		for (int i = 0; i < s->logiclen; ++i)
		{
			s->freefn((char *)s->elems + i * s->elemSize);
		}
	}
	free(s->elems);
}

/*Checks whether stack is empty or not*/
int isEmpty(stack *s)
{
	return s->logiclen == 0;
}

/*Extend the stack double the size
As it is static, this funtion is not visible out this file*/
static void stackGrow(stack *s)
{
	s->alloclen *= 2;
	s->elems = realloc(s->elems, s->alloclen * s->elemSize);
	assert(s->elems != NULL);
}

/*Push the element onto stack whose address is passed to elemAddr*/
void stackPush(stack *s, void *elemAddr)
{
	if (s->logiclen == s->alloclen)
		stackGrow(s);
	//Calculate the starting address of next free location
	/*Temporarily typecast the s->elems to char* so that we can do pointer arithmatic*/
	void *target = (char*)s->elems + s->logiclen * s->elemSize;
	//Copies the elemSize bytes from elemAddr to target
	memcpy(target, elemAddr, s->elemSize);
	s->logiclen++;
}

/*Pops an element from stack*/
void stackPop(stack *s, void *elemAddr)
{
	s->logiclen = s->logiclen - 1;
	/*Calculate the starting address of the block where we last pushed an element*/
	void *source = (char*)s->elems + s->logiclen * s->elemSize;
	/*Copies elemSize bytes or bit pattern stored in source to elemAddr*/
	memcpy(elemAddr, source, s->elemSize);
}

/*This is a helper function which can free space allocated to a string*/
void freeString(void *vp)
{
	/*As in disposeStack when this function in invoked it is passed actually a char**
	So we first type cast it then deference it once to actually free the space allocated to the string
	not the space in the stack*/
	free(*(char **)vp);
}

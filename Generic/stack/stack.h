
typedef struct
{
	void *elems;//Points to an array, where each element is of size  elemSize
	int alloclen; //It is the total number of elements that can be stored
	int logiclen; //Current size of stack in use
	int elemSize; //Size of each element in use, it is needed as we are using generic pointer
	void (*freefn)(void*); //A pointer to a function which will be called back to free allocated sapce
} stack;

void newStack(stack *, int, void (*freefn)(void *));
void disposeStack(stack *);
static void stackGrow(stack *);
void stackPush(stack *, void *);
void stackPop(stack *, void *);
int isEmpty(stack *);
void freeString(void *);//Function to free space allocated to char*

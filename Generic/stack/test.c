#include <stdio.h>
#include <string.h>
#include "stackGeneric.h"

/*Driver code*/

int main()
{
	char *c[] = {"All", "Bob", "Alice"};
	int i, x, n;
	n = sizeof(c) / sizeof(c[0]);
	// stack s;
	stack stackString;
	// newStack(&s, sizeof(int), NULL);
	newStack(&stackString, sizeof(char*), freeString);
	/*freeString is the helper function,
	which can free space allocated to string*/

	// for (i = 0; i < 10; ++i)
	// {
	// 	stackPush(&s, &i);
	// }
	// for (i = 0; i < 10; ++i)
	// {
	// 	stackPop(&s, &x);
	// 	printf("%d\n", x);
	// }
	for (i = 0; i < n; i++)
	{
		char *new = strdup(c[i]);
		stackPush(&stackString, &new);
	}
	char *temp;
	for (i = 0; i < n; i++)
	{
		stackPop(&stackString, &temp);
		printf("%s\n", temp);
	}
	// disposeStack(&s);
	disposeStack(&stackString);
	return 0;
}

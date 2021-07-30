#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Function to compare strings*/
int StrCmp(void *s1, void *s2) {
	char *c1 = *(char **)s1;
	char *c2 = *(char **)s2;
	return strcmp(c1, c2);
}

/*Function to compare ints*/
int cmpInt(void *vp1, void *vp2) {
	int a = *(int *)vp1;
	int b = *(int *)vp2;
	return a - b;
}



void* lsearch(void *base, void *key, int n, int elemSize, int (*cmp)(void *, void *)) { //Here cmp is a pointer to function
//	printf("No of elements %d\n",n);

	for (int i = 0; i < n; i++) {
		void *elemAddr = (char *)base + i * elemSize;
		if (cmp(elemAddr, key)  == 0)
			return elemAddr;
	}
	return NULL;
}


int main() {
	/*Linear search for an array of integers*/
	int a[] = {1, 2, 6, 9, 3, 4, 32, 45, 1212};
	int n = sizeof(a) / sizeof(int);
	int key = 45;

	int *found = lsearch(a, &key, n, sizeof(int), cmpInt); //Here cmpInt is used a callback function,which compares two ints
	if (found == NULL)
	{
		printf("Given key %d is not in the array\n", key);
	} else {
		printf("Given key %d is present in position %d\n", key, (int)(found - a + 1));
	}

	/*Doing linear search for an array of strings*/
	char *ch[] = {"Ab", "efrg", "work", "hello", "g#"};
	char *s = "work";
	int n1 = 5;
	char **found1 = lsearch(&ch, &s, n1, sizeof(char*), StrCmp); //StrCmp is used as a callback function,which compares two char *

	if (found1 != NULL) {
		//	printf("Element is at position %d\n",(int)(found-a+1));
		printf("Given string %s is present in position %d\n", *found1, (int)(found1 - ch + 1));
	} else {
		printf("String %s is  not found\n",s);
	}

	return 0;
}

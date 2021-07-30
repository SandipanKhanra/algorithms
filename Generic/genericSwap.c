#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void genericSwap(void *vp1,void *vp2,int elemSize){

	/*Sets aside storage for elemSize many characters
	 * Acts as a temporary storage*/
	char buffer[elemSize];
	/*Copies the bit pattern stored at location pointed by vp1 to
	 * buffer one byte at a time in total elemSize bytes*/
	memcpy(buffer,vp1,elemSize);
	/*Similarly copies bit pattern from location pointed by vp2 to location poin
	 * -ted by vp1*/
	memcpy(vp1,vp2,elemSize);
	memcpy(vp2,buffer,elemSize);
}

int main(){
	
	int a = 23;
	int b = 465;
	genericSwap(&a,&b,sizeof(int));

	printf("%d %d\n",a,b);


	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

int main(void) {
	double moo[16];
	int i;
	PriorityQueueRef Q;
	FILE * out = fopen("outfile","w");

	moo[1] = 23.3;
	moo[2] = 59.1;
	moo[3] = 35.9;
	moo[4] = 95.5;
	moo[5] = 15.5;
	moo[6] = 67.1;
	moo[7] = 83.2;
	moo[8] = 74.2;
	moo[9] = 01.6;
	moo[10] = 19.4;
	moo[11] = 22.9;
	moo[12] = 45.3;
	moo[13] = 34.4;
	moo[14] = 61.8;
	moo[15] = 47.3;
/*
	for(i=1;i<=15;i++) { printf("%d: %.1f\n",i,moo[i]); }
*/
	Q = newPriorityQueue(15,moo);
	printPriorityQueue(Q,out);

	decreaseKey(Q,4,2.8);
	printPriorityQueue(Q,out);

	deleteMin(Q);
	printPriorityQueue(Q,out);

	fclose(out);
	return 0;
}

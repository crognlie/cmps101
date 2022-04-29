#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

typedef struct PriorityQueue {
	int * front;
	int * back;
	double * key;
	int heapsize;
	int length;
} PriorityQueue;

/* Other Methods */
int left(int);
int right(int);
int parent(int);
void buildHeap(PriorityQueueRef);
void heapify(PriorityQueueRef, int);
void swap(PriorityQueueRef, int, int);

PriorityQueueRef newPriorityQueue(int n, double* key) {
	int i;
	PriorityQueueRef Q = malloc(sizeof(PriorityQueue));
	Q->front = malloc((n+1)*sizeof(int));
	Q->back  = malloc((n+1)*sizeof(int));
	Q->heapsize = n;
	Q->length = n;
	Q->key = key;
	for(i=1;i<=n;i++) { Q->front[i] = Q->back[i] = i; }
	buildHeap(Q);
	return Q;
}

void freePriorityQueue(PriorityQueueRef *Q) {
	free((*Q)->front);
	free((*Q)->back);
	free(*Q);
	*Q = NULL;
}

void buildHeap(PriorityQueueRef Q) {
	int i;
	for(i = parent(Q->heapsize); i>=1; i--) { heapify(Q,i); }
}

int left(int i) { return 2 * i; }
int right(int i) { return 2 * i + 1; }
int parent(int i) { return (i - (i%2)) / 2; }

void heapify(PriorityQueueRef Q, int i) {
	int l,r,n,largest;
	l = left(i);
	r = right(i);
	n = Q->heapsize;
	largest=(l <= n && Q->key[Q->front[l]] < Q->key[Q->front[i]]) ? l : i;
	if(r <= n && Q->key[Q->front[r]] < Q->key[Q->front[largest]])
		{ largest = r; }
	if(largest != i) { swap(Q,i,largest); heapify(Q,largest); }
}

void swap(PriorityQueueRef Q, int i, int j) {
	int hold;

	hold = Q->front[i];
	Q->front[i] = Q->front[j];
	Q->front[j] = hold;

	hold = Q->back[Q->front[i]];
	Q->back[Q->front[i]] = Q->back[Q->front[j]];
	Q->back[Q->front[j]] = hold;
}

int getNumElements(PriorityQueueRef Q) { return Q->heapsize; }
int getMin(PriorityQueueRef Q) { return Q->front[1]; }
int inQueue(PriorityQueueRef Q, int u) {
	return (Q->back[u] <= Q->heapsize && Q->back[u] >= 1) ? 1 : 0;
}

void deleteMin(PriorityQueueRef Q) {
	swap(Q,1,Q->heapsize--);
	heapify(Q,1);
} 

void decreaseKey(PriorityQueueRef Q, int u, double k) {
	if( k >= Q->key[u] ) {
		printf("decreaseKey() with larger value: u,k: %d %f\n",u,k);
		exit(1);
	}
	if( u < 1 || u > Q->heapsize) {
		printf("decreaseKey() with u OOB\n"); exit(1);
	}
	/* DECREASE KEY */
	Q->key[u] = k;
	u = Q->back[u];
	while( u > 1 && Q->key[u] < Q->key[parent(u)]){
		swap(Q,u,parent(u));
		u = parent(u);
	}
}

void printPriorityQueue(PriorityQueueRef Q, FILE* out) {
	int i;
	for(i=1; i<=Q->heapsize; i++) {
		fprintf(out,"%.1f ",Q->key[Q->front[i]]);
		printf (    "%.1f ",Q->key[Q->front[i]]);
		if(Q->front[Q->back[i]] != i) { exit(1); }
		if(Q->back[Q->front[i]] != i) { exit(1); }
	}
	fprintf(out,"\n"); printf("\n");
}

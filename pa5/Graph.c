/*
	Graph.c

	Created by Colin Rognlie on 8/4/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa5

	Function definitions, preconditions, etc. are in Graph.h
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "PriorityQueue.h"

#define INF 100000
#define NIL 0

/* Data Structure */

typedef struct Graph{
	int order;
	ListRef * adj;
	double * key;
	double ** weight;
	int * parent;
} Graph;

/* Creation & Destruction */

GraphRef newGraph(int n) {
	int i,j;
	GraphRef H;

	if ( n < 1 ) { printf("newGraph(n<1)\n"); exit(1); }
	
	H           = malloc(sizeof(Graph));
	H->adj      = malloc((n+1)*sizeof(ListRef));
	H->parent   = malloc((n+1)*sizeof(int));
	H->key      = malloc((n+1)*sizeof(double));
	H->weight   = malloc((n+1)*sizeof(double *));
	H->order    = n;

	for(i=1; i<=n; i++) {
		H->adj[i] = newList();
		H->key[i] = H->parent[i] = 0;
		H->weight[i] = malloc((n+1)*sizeof(double));
		for(j=1; j<=n; j++) { H->weight[i][j] = INF; }
	}

	return H;
}

void freeGraph(GraphRef *pG) {
	int i;
	GraphRef G = *pG;
	if( pG == NULL ) { printf("freeGraph() on NULL pointer\n"); exit(1); }
	for ( i=1; i <= G->order; i++) {
		freeList( &G->adj[i] );
		free( G->weight[i] );
	}
	free(G->key);
	free(G->adj);
	free(G->weight);
	free(G->parent);
	free(G);
	*pG = NULL;
}

/* Access Procedures */
int getOrder(GraphRef G) { return G->order; }
int getParent(GraphRef G, int u) {
	if( u > getOrder(G) || u < 1 )
		{ printf("u out of bounds in getParent()\n"); exit(1); }
	return G->parent[u];
}
double getEdgeWeight(GraphRef G, int u, int v) {
	if( u > getOrder(G) || u < 1 )
		{ printf("u out of bounds in getEdgeWeight()\n"); exit(1); }
	return G->weight[u][v];
}

/* Manipulation Procedures */
void addEdge(GraphRef G, int u, int v, double wt) {
	if( u > getOrder(G) || u < 1 || v > getOrder(G) || v < 1 )
		{ printf("u||v out of bounds in addEdge(u,v)\n"); exit(1); }
	if( u == v ) { printf("u=v in addEdge(u,v)\n"); exit(1); }
	insertAfterLast(G->adj[u],v);
	insertAfterLast(G->adj[v],u);
	G->weight[u][v] = G->weight[v][u] = wt;
}

void Prim(GraphRef G, int r) {
	int u,v;
	double w;
	int n = getOrder(G);
	PriorityQueueRef Q;
	for (u=1; u<=n; u++) { G->key[u]=INF; G->parent[u]=NIL; }
	G->key[r] = 0;
	Q = newPriorityQueue(n,G->key);
	while(getNumElements(Q)) {
		u = getMin(Q); deleteMin(Q);
		for( moveFirst(G->adj[u]); !offEnd(G->adj[u]); moveNext(G->adj[u])){
			v = getCurrent(G->adj[u]);
			w = G->weight[u][v];
			if(inQueue(Q,v) && w < G->key[v]) {
				G->parent[v] = u;
				decreaseKey(Q,v,w);
			}
		}
	}
}

/* Other Procedures */
void printGraph(GraphRef G, FILE* out) {
	int i;
	fprintf(out, "Adjacency list representation of G:\n");
	for(i=1;i<=getOrder(G);i++) {
		fprintf(out, "%d:", i);
		if(!isEmpty(G->adj[i])) {
			moveFirst(G->adj[i]);
			while(!offEnd(G->adj[i])) {
				fprintf(out, " %d", getCurrent(G->adj[i]));
				moveNext(G->adj[i]);
			}
		}
		fprintf(out, "\n");
	}
}

GraphRef copyGraph(GraphRef G) {
	GraphRef H;
/*
	int i,j,n;
	n = getOrder(G);

	if ( n < 1 ) { printf("copyGraph() on graph of order < 1\n"); exit(1); }
	
	H           = malloc(sizeof(Graph));
	H->adj      = malloc((n+1)*sizeof(ListRef));
	H->parent   = malloc((n+1)*sizeof(int));
	H->key      = malloc((n+1)*sizeof(int));
	H->weight   = malloc((n+1)*sizeof(double *));
	H->order    = n;

	for(i=1; i<=n; i++) {
		H->parent[i]   = G->parent[i];

		H->adj[i] = copy(G->adj[i]);
	}
*/
	return H;
}

/*
	Graph.c

	Created by Colin Rognlie on 8/4/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa4

	Function definitions, preconditions, etc. are in Graph.h
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GREY 1
#define BLACK 2

/* Data Structure */

typedef struct Graph{
	int order;
	ListRef *adj;
	int *color;
	int *discover;
	int *finish;
	int *parent;
} Graph;

/* Creation & Destruction */

GraphRef newGraph(int n) {
	int i;
	GraphRef H;

	if ( n < 1 ) { printf("newGraph(n<1)\n"); exit(1); }
	
	H           = malloc(sizeof(Graph));
	H->adj      = malloc((n+1)*sizeof(ListRef));
	H->color    = malloc((n+1)*sizeof(int));
	H->discover = malloc((n+1)*sizeof(int));
	H->finish   = malloc((n+1)*sizeof(int));
	H->parent   = malloc((n+1)*sizeof(int));
	H->order    = n;

	for(i=1; i<=n; i++) {
		H->color[i] = H->discover[i] = H->finish[i] = H->parent[i] = 0;
		H->adj[i] = newList();
	}

	return H;
}

GraphRef transpose(GraphRef G) {
	int n = getOrder(G);
	GraphRef H = newGraph(n);
	int i;

	for (i=1;i<=n;i++) {
		if(!isEmpty(G->adj[i])) {
			moveFirst(G->adj[i]);
			while (!offEnd(G->adj[i])) {
				addDirectedEdge(H,getCurrent(G->adj[i]),i);
				moveNext(G->adj[i]);
			}
		}
	}
	return H;
}

GraphRef copyGraph(GraphRef G) {
	int i,n;
	GraphRef H;

	n = getOrder(G);

	if ( n < 1 ) { printf("copyGraph() on graph of order < 1\n"); exit(1); }
	
	H           = malloc(sizeof(Graph));
	H->adj      = malloc((n+1)*sizeof(ListRef));
	H->color    = malloc((n+1)*sizeof(int));
	H->discover = malloc((n+1)*sizeof(int));
	H->finish   = malloc((n+1)*sizeof(int));
	H->parent   = malloc((n+1)*sizeof(int));
	H->order    = n;

	for(i=1; i<=n; i++) {
		H->color[i]    = G->color[i]; 
		H->discover[i] = G->discover[i]; 
		H->finish[i]   = G->finish[i];
		H->parent[i]   = G->parent[i];
		H->adj[i] = copy(G->adj[i]);
	}

	return H;
}

void freeGraph(GraphRef *pG) {
	int i;
	GraphRef G = *pG;
	if( pG == NULL ) { printf("freeGraph() on NULL pointer\n"); exit(1); }
	for ( i=0; i <= G->order; i++) { freeList( &G->adj[i] ); }
	free(G->color);
	free(G->discover);
	free(G->finish);
	free(G->parent);
	free(G);
	*pG = NULL;
}

/* Access Procedures */
int getOrder(GraphRef G) { return G->order; }
int getParent(GraphRef G, int u) {
	if( u > getOrder(G) || u < 1 ) { printf("u out of bounds in getParent()\n"); exit(1); }
	return G->parent[u];
}

int getDiscover(GraphRef G, int u) {
	if( u > getOrder(G) || u < 1 ) { printf("u out of bounds in getDiscover()\n"); exit(1); }
	return G->discover[u];
}

int getFinish(GraphRef G, int u) {
	if( u > getOrder(G) || u < 1 ) { printf("u out of bounds in getFinish()\n"); exit(1); }
	return G->finish[u];
}

/* Manipulation Procedures */
void addDirectedEdge(GraphRef G, int u, int v) {
	if( u > getOrder(G) || u < 1 || v > getOrder(G) || v < 1 ) {
		printf("u||v out of bounds in addDirectedEdge(u,v)\n"); exit(1);
	}
	insertAfterLast(G->adj[u],v);
}

void DFS_visit(GraphRef G, ListRef S, int u, int *time) {
	int v;
	G->color[u]++;
	G->discover[u] = ++(*time);
	if(!isEmpty(G->adj[u])) {
		moveFirst(G->adj[u]);
		while(!offEnd(G->adj[u])) {
			v = getCurrent(G->adj[u]);
			if( G->color[v] == WHITE ) { G->parent[v] = u; DFS_visit(G,S,v,time); }
			if(!offEnd(G->adj[u])) { moveNext(G->adj[u]); }
		}
	}
	G->color[u]++;
	G->finish[u] = ++(*time);
	insertBeforeFirst(S,u);
}

void DFS(GraphRef G, ListRef S) {
	int i,n,time;
	ListRef P;
	if (getOrder(G) != getLength(S)) { printf("order(G) != length(S) in DFS()\n"); exit(1); }
	P = copy(S);
	makeEmpty(S);
	n = getOrder(G);
	time = 0;
	for (i=1; i<= n; i++) {
		G->color[i] = G->discover[i] = G->finish[i] = G->parent[i] = 0;
	}
	if(!isEmpty(P)) {
		moveFirst(P);
		while(!offEnd(P)) {
			if(G->color[getCurrent(P)] == 0) { DFS_visit(G,S,getCurrent(P),&time); }
			moveNext(P);
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

void printStrComp(GraphRef G, ListRef L, FILE* out) {
	int nsc = 0;
	int i,j;
	int n = getOrder(G);
	int compnum[n+1];

	if(!isEmpty(L)) {
		for (moveFirst(L); !offEnd(L); moveNext(L)) {
			if ( !getParent(G,getCurrent(L)) ) { nsc++; }
		}
	}
	fprintf(out, "\nG contains %d strongly connected components:\n",nsc);
	j = nsc;
	if(!isEmpty(L)) {
		for (moveFirst(L); !offEnd(L); moveNext(L)) {
			if ( !getParent(G,getCurrent(L)) ) { j--; }
			compnum[getCurrent(L)] = j+1;
		}
	}
	for(i=1; i<=nsc; i++) {
		fprintf(out, "Component %d:",i);
		for(j=1; j<=n; j++) { if (compnum[j]==i) {fprintf(out, " %d",j);} }
		fprintf(out, "\n");
	}
}

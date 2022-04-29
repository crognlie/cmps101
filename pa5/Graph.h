/*
	Graph.h

	Created by Colin Rognlie on 8/4/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa5
*/
#include "List.h"

/* Definition of pointer to Graph */
typedef struct Graph* GraphRef;

/* Creation & Destruction */
/* newGraph returns a reference to a new Graph structure */
GraphRef newGraph(int);
/* copyGraph returns a reference to a copy of a Graph */
GraphRef copyGraph(GraphRef);
/* freeGraph destroys a Graph and nullifies the pointer to it */
void freeGraph(GraphRef *);

/* Access Procedures */
/* getOrder returns the number of vertices in a Graph */
int getOrder(GraphRef);
/* getParent returns the parent of a vertex in a Graph
   pre: 1 <= u <= getOrder(G) */
int getParent(GraphRef, int);
double getEdgeWeight(GraphRef, int, int);

/* Manipulation Procedures */
/* addEdge adds an undirected edge between two vertices
   pre: 1 <= u,v <= getOrder(G) */
void addEdge(GraphRef, int, int, double);
void Prim(GraphRef G, int r);

/* Other Procedures */
/* printGraph prints the adjacency list of a graph to a file */
void printGraph(GraphRef, FILE *);

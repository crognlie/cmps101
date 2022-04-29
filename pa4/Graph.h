/*
	Graph.h

	Created by Colin Rognlie on 8/4/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa4
*/
#include "List.h"

/* Definition of pointer to Graph */
typedef struct Graph* GraphRef;

/* Creation & Destruction */
/* newGraph returns a reference to a new Graph structure */
GraphRef newGraph(int);
/* transpose returns a reference to a transpose of a Graph */
GraphRef transpose(GraphRef);
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
/* getDiscover returns the discover time of a vertex
   pre: 1 <= u <= getOrder(G) */
int getDiscover(GraphRef, int);
/* getFinish returns the finish time of a vertex
   pre: 1 <= u <= getOrder(G) */
int getFinish(GraphRef, int);

/* Manipulation Procedures */
/* addDirected Edge adds a one way edge between two vertices
   pre: 1 <= u,v <= getOrder(G) */
void addDirectedEdge(GraphRef, int, int);
/* DFS runs depth-first-search on a Graph in List order
   pre: getLength(L) = getOrder(G) */
void DFS(GraphRef, ListRef);

/* Other Procedures */
/* printGraph prints the adjacency list of a graph to a file */
void printGraph(GraphRef, FILE *);
/* printStrComp prints the Strongly Connected Componenets of a graph
   to a file */
void printStrComp(GraphRef, ListRef, FILE *);

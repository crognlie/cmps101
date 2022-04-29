/*
	GraphClient.c

	Created by Colin Rognlie on 8/4/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa4
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(void) {
	FILE *fp;
	ListRef L;
	GraphRef G, GT;
	int n = 8;
	int i;

	fp = fopen("out_file", "w");

	L = newList();
	G = newGraph(n);

	for(i=1;i<=n;i++) { insertAfterLast(L,i); }
	addDirectedEdge(G,1,2);
	addDirectedEdge(G,2,3);
	addDirectedEdge(G,2,5);
	addDirectedEdge(G,2,6);
	addDirectedEdge(G,3,4);
	addDirectedEdge(G,3,7);
	addDirectedEdge(G,4,3);
	addDirectedEdge(G,4,8);
	addDirectedEdge(G,5,1);
	addDirectedEdge(G,5,6);
	addDirectedEdge(G,6,7);
	addDirectedEdge(G,7,6);
	addDirectedEdge(G,7,8);
	addDirectedEdge(G,8,8);

	GT = transpose(G);
	DFS(G,L);
	DFS(GT,L);

	printGraph(G,fp);
	printStrComp(GT,L,fp);
	return 0;
}

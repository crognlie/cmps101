/*
	FindComponents.c

	Created by Colin Rognlie on 8/4/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa4
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char * argv[]) {
	FILE *in, *out;
	int i,n,insrc,indst;
	GraphRef G,GT;
	ListRef L = newList();

	/* Check arguments */
	if ( argc != 3 ) { printf("Usage: %s infile outfile\n", argv[0]); exit(1); }

	/* Read input */
	in  = fopen(argv[1],"r");
	if( in==NULL ) { printf("Unable to open file %s for reading\n", argv[1]); exit(1); }
	fscanf(in,"%d",&n);
	G = newGraph(n);
	for(i=1;i<=n;i++) { insertAfterLast(L,i); }
	while( fscanf(in, "%d %d", &insrc, &indst)!=EOF && insrc && indst ) {
		addDirectedEdge(G,insrc,indst);
	}
	fclose(in);

	/* Calculations & Output */
	out = fopen(argv[2],"w");
	if( out==NULL ){ printf("Unable to open file %s for writing\n", argv[2]); exit(1); }
	printGraph(G,out);
	GT = transpose(G);
	DFS(G,L);
	DFS(GT,L);
	printStrComp(GT,L,out);
	fclose(out);

	return 0;
}

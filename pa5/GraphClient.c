/*
	GraphClient.c

	Created by Colin Rognlie on 8/4/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa5
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char * argv[]) {
	FILE *in, *out;
	int n,insrc,indst,edgecount;
	double inwt;
	GraphRef G;

	/* Check arguments */
	if ( argc != 3 ) { printf("Usage: %s infile outfile\n", argv[0]); exit(1); }

	/* Read input */
	in = fopen(argv[1],"r");
	if( in==NULL ) { printf("Unable to open file %s for reading\n", argv[1]); exit(1); }
	fscanf(in,"%d",&n);
	G = newGraph(n);
	fscanf(in,"%d",&edgecount);
	while(edgecount && fscanf(in, "%d %d %lf",&insrc,&indst,&inwt)!=EOF) {
		addEdge(G,insrc,indst,inwt);
		edgecount--;
	}
	fclose(in);

	out = fopen(argv[2], "w");
	printGraph(G,out);
	fclose(out);
	return 0;
}

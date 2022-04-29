/*
	List.c

	Created by Colin Rognlie on 7/3/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa2
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

/* Prototypes */
int calcShuffle (int n);
void shuffle(ListRef L);
int main (int argc, char* argv[]);

/* int main (int argc, char* argv[])
// Parses command line input, calls calcShuffle, prints output */
int main (int argc, char* argv[]) {
	int n;
	if(argc != 2) { printf("Usage: %s number\n", argv[0]); exit(1); }
	n = atoi(argv[1]);
	if ( n < 1 ) { printf("Input number must be 1 or greater.\n"); exit(1); }
	printf("%d\n", calcShuffle(n));
	return 0;
}

/* void calcShuffle (int n)
// Calculated number of shuffles to return to starting deck */
int calcShuffle (int n) {
	/* Initialize variables */
	ListRef deck = newList();
	ListRef startdeck = newList();
	int i, shuffles;
	/* Create initial decks */
	for (i=1; i<=n; i++) { insertAfterLast(deck,i); }
	startdeck = copy(deck);
	/* Shuffle until return to starting deck */
	shuffles = 1;
	for( shuffle(deck); !equals(deck,startdeck); shuffle(deck) ) { shuffles++; }
	return shuffles;
}

/* void shuffle(L) // Shuffles deck according to given algorithm */
void shuffle(ListRef L) {
	/* Initialize two half decks */
	ListRef A = newList();
	ListRef B = newList();
	/* Split main deck into top and bottom halves */
	while ( !isEmpty(L) ) {
		insertAfterLast( A,getFirst(L) ); deleteFirst(L);
		if ( !isEmpty(L) ) {
			insertBeforeFirst( B,getLast(L) ); deleteLast(L);
		}
	}
	/* Shuffle halves together back into main deck */
	while ( !isEmpty(A) || !isEmpty(B) ) {
		if ( !isEmpty(A) ) { insertBeforeFirst(L,getLast(A)); deleteLast(A); }
		if ( !isEmpty(B) ) { insertBeforeFirst(L,getLast(B)); deleteLast(B); }
	}
}

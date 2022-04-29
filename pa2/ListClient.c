/*
	ListClient.c

	Created by Colin Rognlie on 7/3/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa2
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

/* TESTNODES is the number of nodes in the test lists. */
#define TESTNODES 1000
#define TESTNUM (TESTNODES/2)+1

/* void listClientError (char em[]) // Prints error message  and exits */
void listClientError (char em[]) { printf("%s\n",em); exit(1); }

/* int main (int argc, char* argv[]) // tests List structure and functions */
int main (int argc, char* argv[]) {
	ListRef A,B,C,D;
	int num, i; 

	A = newList(); B = newList();
	num = TESTNUM;

	/* Add some data */
	for( i = 1; i < num; i++ ) { insertAfterLast(A,i); insertBeforeFirst(B,i); }
	moveFirst(A); moveLast(B);
	for( i = 1; i < num; i++ ) {
		insertBeforeCurrent(A,num-i); moveNext(A);
		insertAfterCurrent(B,num-i); movePrev(B);
	}

	/* 1 & 2 test
		move{First,Last,Next,Prev}, get(First,Last,Length), equals
		insertBefore{First,Current}, insertAfter{Current,Last} */
	if ( ! equals(A,B) ) { listClientError("Test 1 Failure"); }
	if ((getFirst(A) != getLast(B)) || ( getLast(A) != getFirst(B))) {
		listClientError("Test 2 Failure");
	}

	/* Move through list */
	moveLast(A); moveFirst(B);
	for( i = 1; i < (2*num)-2; i++ ) { movePrev(A); moveNext(B); }

	/* 3 tests move{Prev,Next}, at{First,Last}
	then move one more 
	   4 tests offEnd */
	if ( ! atFirst(A) || ! atLast(B) ) { listClientError("Test 3 Failure"); }
	movePrev(A); moveNext(B);
	if ( ! offEnd(A) || ! offEnd(B) ) { listClientError("Test 4 Failure"); }

	/* Move halfway through data */
	moveFirst(A); moveLast(B);
	for( i = 1; i < num; i++ ) { moveNext(A); movePrev(B); }

	/* 5 tests getCurrent */
	if ( getCurrent(A) != getCurrent(B) ) { listClientError("Test 5 failure"); }

	/* Delete current, first, last */
	deleteCurrent(A); deleteFirst(A); deleteLast(A);
	deleteCurrent(B); deleteFirst(B); deleteLast(B);

	/* 6 tests delete{First,Current,Last} */
	if ( ! equals(A,B) ) { listClientError("Test 6 Failure"); }

	/* Move halfway through data */
	moveFirst(A); moveLast(B);
	for( i = 1; i < num-1; i++ ) { moveNext(A); movePrev(B); }

	/* 7 tests getCurrent */
	if ( getCurrent(A) != getCurrent(B) ) { listClientError("Test 7 Failure"); }

	/* Make a copy */
	C = copy(A);
	/* 8 tests copy */
	if ( ! equals(B,C) ) { listClientError("Test 8 Failure"); }

	/* delete lists, make new lists */
	makeEmpty(A); makeEmpty(B); makeEmpty(C);
	for ( i = 1; i < num; i++ ) {
		insertAfterLast(A,i);
		insertAfterLast(B,i+num-1);
	}
	for ( i = 1; i < 2*num-1; i++ ) { insertAfterLast(C,i); }
	D = newList();
	D = cat(A,B);

	/* 9 tests makeEmpty, cat */
	if ( ! equals(C,D) ) { listClientError("Test 9 Failure"); }

	printf("All List tests passed.\n");
	return 0;
}

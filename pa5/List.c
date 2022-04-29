/*
	List.c

	Created by Colin Rognlie on 7/1/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa5

	Function definitions, preconditions, etc. are in List.h
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

/* Epistemology */

#define FALSE 0
#define TRUE 1

/* Data Structures */

typedef struct Node{
	int data;
	struct Node* prev; struct Node* next;
} Node;

typedef Node* NodeRef;

typedef struct List{
	NodeRef front; NodeRef current; NodeRef back;
	int length;
} List;

/* Local Prototypes */

void validList(ListRef L);

/* Creation & Destruction */

NodeRef newNode(int node_data){
	NodeRef N = malloc(sizeof(Node));
	N->data = node_data;
	N->prev = N->next = NULL;
	return(N);
}

void freeNode(NodeRef* pN){
	if( pN!=NULL && *pN!=NULL ){ free(*pN); *pN = NULL; }
}

ListRef newList(void){
	ListRef L;
	L = malloc(sizeof(List));
	L->front = L->current = L->back = NULL;
	L->length = 0;
	return(L);
}

void freeList(ListRef* pL){
	if( pL==NULL ) { printf("freeList() on NULL pointer\n"); exit(1); }
	validList(*pL);
	makeEmpty(*pL);
	free(*pL);
	*pL = NULL;
}

/* Access Procedures */

int isEmpty (ListRef L) { validList(L); return (getLength(L) == 0); }

int atFirst (ListRef L) {
	validList(L);
	return ( (!isEmpty(L)) && (L->front == L->current) );
}

int atLast (ListRef L) {
	validList(L);
	return ( (!isEmpty(L)) && (L->back == L->current) );
}

int offEnd (ListRef L) {
	validList(L);
	return (  (!isEmpty(L)) && (L->current == NULL) );
}

int getFirst (ListRef L) {
	validList(L);
	if( isEmpty(L) ){
		printf("List Error: calling getFirst() on an empty List\n"); exit(1);
	}
	return(L->front->data);
}

int getLast (ListRef L) {
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling getLast() on an empty List\n"); exit(1);
	}
	return (L->back->data);
}

int getCurrent (ListRef L) {
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling getCurrent() on an empty List\n"); exit(1);
	} else if ( offEnd(L) ) {
		printf("List Error: calling getCurrent() on an offEnd List\n"); exit(1);
	}
	return (L->current->data);
}

int getLength (ListRef L) { validList(L); return (L->length); }

int equals (ListRef A, ListRef B) {
	NodeRef C, D;
	validList(A); validList(B);
	if ( getLength(A) != getLength(B) ) { return FALSE; }
	if ( isEmpty(A) || isEmpty(B) ) {
		if ( isEmpty(A) && isEmpty(B) ) { return TRUE; }
		else { return FALSE; }
	}
	C = A->front; D = B->front;
	while ( C != NULL ) {
		if (C->data != D->data) { return FALSE; }
		C = C->next; D = D->next;
	}
	if ( C == NULL && D == NULL ) { return TRUE; }
	return FALSE;
}

/* Manipulation Procedures */

void moveFirst (ListRef L) {
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling moveFirst() on an empty List\n"); exit(1);
	}
	L->current = L->front;
}

void moveLast (ListRef L) {
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling moveLast() on an empty List\n"); exit(1);
	}
	L->current = L->back;
}

void movePrev (ListRef L) {
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling movePrev() on an empty List\n"); exit(1);
	} else if ( offEnd(L) ) {
		printf("List Error: calling movePrev() on an offEnd List\n"); exit(1);
	}
	L->current = L->current->prev;
}
void moveNext (ListRef L) {
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling moveNext() on an empty List\n"); exit(1);
	} else if ( offEnd(L) ) {
		printf("List Error: calling moveNext() on an offEnd List\n"); exit(1);
	}
	L->current = L->current->next;
}

void insertBeforeFirst(ListRef L, int data) {
	NodeRef N;
	validList(L);
	N = newNode(data);
	if ( isEmpty(L) ) {
		L->front = L->back = N;
	} else {
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	L->length++;
}

void insertAfterLast(ListRef L, int data) {
	NodeRef N;
	validList(L);
	N = newNode(data);
	if ( isEmpty(L) ) {
		L->front = L->back = N;
	} else {
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->length++;
}

void insertBeforeCurrent(ListRef L, int data) {
	NodeRef N, P, C;
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling insertBeforeCurrent() on an empty List\n");
		exit(1);
	} else if ( offEnd(L) ) {
		printf("List Error: calling insertBeforeCurrent() on an offEnd List\n");
		exit(1);
	}
	if ( atFirst(L) ) { insertBeforeFirst(L, data); }
	else {
		N = newNode(data);
		C = L->current;
		P = C->prev;
		P->next = C->prev = N;
		N->next = C;
		N->prev = P;
		L->length++;
	}
}

void insertAfterCurrent(ListRef L, int data) {
	NodeRef N, C, A;
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling insertBeforeCurrent() on an empty List\n");
		exit(1);
	} else if ( offEnd(L) ) {
		printf("List Error: calling insertBeforeCurrent() on an offEnd List\n");
		exit(1);
	}
	if ( atLast(L) ) { insertAfterLast(L, data); }
	else {
		N = newNode(data);
		C = L->current;
		A = C->next;
		C->next = A->prev = N;
		N->prev = C;
		N->next = A;
		L->length++;
	}
}

void deleteFirst(ListRef L) {
	NodeRef old;
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling deleteFirst() on an empty List\n");
		exit(1);
	}
	if ( L->front == L->current ) { L->current = NULL; }
	if ( L->back == L->front ) { makeEmpty(L); }
	else {
		old = L->front;
		L->front = old->next;
		L->front->prev = NULL;
		freeNode(&old);
		L->length--;
	}
}

void deleteLast(ListRef L) {
	NodeRef old;
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling deleteLast() on an empty List\n");
		exit(1);
	}
	if ( L->back == L->current ) { L->current = NULL; }
	if ( L->back == L->front ) { makeEmpty(L); }
	else {
		old = L->back;
		L->back = old->prev;
		L->back->next = NULL;
		freeNode(&old);
		L->length--;
	}
}

void deleteCurrent(ListRef L) {
	NodeRef a,b,c;
	validList(L);
	if ( isEmpty(L) ) {
		printf("List Error: calling deleteCurrent() on an empty List\n");
		exit(1);
	} else if ( offEnd(L) ) {
		printf("List Error: calling deleteCurrent() on an offEnd List\n");
		exit(1);
	} else if ( atFirst(L) ) {
		deleteFirst(L);
	} else if ( atLast(L) ) {
		deleteLast(L);
	} else {
		b = L->current;
		a = b->prev;
		c = b->next;
		L->current = NULL;
		a->next = c;
		c->prev = a;
		freeNode(&b);
		L->length--; 
	}
}

/* Other Procedures */

void validList(ListRef L) {
	if ( L == NULL ) { printf("List Error: NULL ListRef\n"); exit(1); }
}

ListRef copy(ListRef L) {
	NodeRef n;
	ListRef nl;
	validList(L);
	nl = newList();
	for (n = L->front; n != NULL; n = n->next ) { insertAfterLast(nl,n->data); }
	return nl;
}

ListRef cat(ListRef A, ListRef B) { 
	NodeRef n;
	ListRef C;
	validList(A); validList(B);
	C = newList();
	for (n = A->front; n != NULL; n = n->next ) { insertAfterLast(C,n->data); }
	for (n = B->front; n != NULL; n = n->next ) { insertAfterLast(C,n->data); }
	return C;
}

void makeEmpty (ListRef L) {
	validList(L);
	if ( getLength(L) == 1 ) {
		L->length = 0;
		L->front = L->current = L->back = NULL;
	}
	while ( !isEmpty(L) ) { deleteFirst(L); }
}

void printList(ListRef L) {
	NodeRef n;
	validList(L);
	for ( n = L->front; n != NULL; n = n->next ) {
		printf("%d",n->data);
		if(n->next != NULL) { printf(" "); }
		else { printf("\n"); }
	}
}

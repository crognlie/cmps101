/*
	List.h

	Created by Colin Rognlie on 7/2/05.
	Copyright 2005. All rights reserved.

	Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa5
*/

#if !defined(_LIST_H_INCLUDE_)
#define _LIST_H_INCLUDE_
#endif

/* Definition of Pointer to List Structure */
typedef struct List* ListRef;

/* Creation & Destruction */

/* ListRef newList() // Creates a new list and returns a reference to it. */
ListRef newList(void);  
/* void freeList(*L) // Destroys a list and nullifies the pointer to it. */
void freeList(ListRef* pL);

/* Access Procedures */

/* int isEmpty(L) // Returns true if list contains no elements. */
int isEmpty(ListRef L);
/* int atFirst(L) // Returns true if current marker refers to first element. */
int atFirst(ListRef L);
/* int atLast(L) // Returns true if current marker refers to last element. */
int atLast(ListRef L);
/* int offEnd(L) // Returns true if no element is current. */
int offEnd(ListRef L);
/* int getFirst(L) // Returns first element in list. */
/* Pre: !isEmpty(L) */
int getFirst(ListRef L);
/* int getLast(L) // Returns last element in list. */
/* Pre: !isEmpty(L) */
int getLast(ListRef L);
/* getCurrent(L) // Returns current element in list. */
/* Pre: !isEmpty(L), !offEnd(L). */
int getCurrent(ListRef L);
/* int getLength(L) // Returns length of list. */
int getLength(ListRef L);
/* int equals(A,B) // Returns true if lists A and B are identical. */
int equals(ListRef A, ListRef B);

/* Manipulation Procedures */

/* void moveFirst(L) // Makes first element current. */
/* Pre: !isEmpty(L) */
/* Post: !offEnd(L) */
void moveFirst(ListRef L);
/* void moveLast(L) // Makes last element current. */
/* Pre: !isEmpty(L) */
/* Post: !offEnd(L) */
void moveLast(ListRef L);
/* void movePrev(L) // Steps the current marker toward beginning of list. */
/* Pre: !isEmpty(L), !offEnd(L) */
void movePrev(ListRef L);
/* void moveNext(L) // Steps the current marker toward end of list. */
/* Pre: !isEmpty(L), !offEnd(L) */
void moveNext(ListRef L);
/* void insertBeforeFirst(L, data) // Adds new element to beginning of list. */
/* Post: !isEmpty(L) */
void insertBeforeFirst(ListRef L, int data);
/* void insertAfterLast(L, data) // Adds new element to end of list. */
/* Post: !isEmpty(L) */
void insertAfterLast(ListRef L, int data);
/* void insertBeforeCurrent(L, data) */
/* Inserts new element just before current. */
/* Pre: !isEmpty(L), !offEnd(L) */
void insertBeforeCurrent(ListRef L, int data);
/* void insertAfterCurrent(L, data) // Inserts element just after current. */
/* Pre: !isEmpty(L), !offEnd(L) */
void insertAfterCurrent(ListRef L, int data);
/* void deleteFirst(L) // Deletes first element. */
/* Pre: !isEmpty(L) */
void deleteFirst(ListRef L); 
/* void deleteLast(L) // Deletes last element. */
/* Pre: !isEmpty(L) */
void deleteLast(ListRef L);
/* void deleteCurrent(L) // Deletes current element. */
/* Pre: !isEmpty(L), !offEnd(L) */
/* Post: offEnd(L) */
void deleteCurrent(ListRef L);

/* Other Procedures */

/* ListRef copy(L) // Returns a ListRef to a copy of the argument list */
ListRef copy(ListRef L);
/* ListRef cat(A,B) */
/* Returns a ListRef to a concatenation of the two argument lists */
ListRef cat (ListRef A, ListRef B);
/* void makeEmpty(L) // Removes all nodes from lists */
void makeEmpty (ListRef L);
/* void printList(L) // Prints out a representation of list */
void printList(ListRef L);

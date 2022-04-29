//
//  List.java
//
//  Created by Colin Rognlie on 6/27/05.
//  Copyright 2005. All rights reserved.
//
//  Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa1
//

public class List {
  // Private Classes
	private class Node {
	  // Fields
		int data;
		Node prev;
		Node next;
	  // Constructor
		Node (int data) {
			this.data = data;
			this.prev = this.next = null;
		}
	  // Other Methods
		// toString
		public String toString () {	return String.valueOf(data); }
	}
  
	// Fields
	Node front;
	Node current;
	Node back;
	int length;
  
	// Constructor
	List () { front = current = back = null; length = 0; }
  
	// Access Procedures
	// boolean isEmpty()
	// Returns true if list contains no elements.
	boolean isEmpty () { return (length == 0); }
	// boolean atFirst()
	// Returns true if current marker refers to first element. 
	boolean atFirst () {
		if ( isEmpty() ) { return false; }
		return ( current == front );
	}
	// boolean atLast()
	// Returns true if current marker refers to last element. 
	boolean atLast () {
		if ( isEmpty() ) { return false; }
		return ( current == back );
	}
	// boolean offEnd()
	// Returns true if no element is current.
	boolean offEnd () { return ( current == null ); }
	// int getFirst()
	// Returns first element in list.
	// Pre: !isEmpty().
	int getFirst () {
		if ( isEmpty() ) { throw new RuntimeException("getFirst() on empty list"); }
		return front.data;		
	}
	// int getLast()
	// Returns last element in list.
	// Pre: !isEmpty(). 
	int getLast () {
		if ( isEmpty() ) { throw new RuntimeException("getLast() on empty list"); }
		return back.data;
	}
	// int getCurrent()
	// Returns current element in list.
	// Pre: !isEmpty(), !offEnd(). 
	int getCurrent () {
		if ( isEmpty() ){ throw new RuntimeException("getCurrent() on empty list");}
		if ( offEnd() ){ throw new RuntimeException("getCurrent() on offEnd list");}
		return current.data;
	}
	// int getLength()
	// Returns length of list.
	int getLength () { return length; }
	// boolean equals(List L)
	// Returns true if this list contains same elements as argument list.
	boolean equals (List L) {
		if ( length != L.length ) {	return false; }
		Node thisList = front;
		Node thatList = L.front;
		while ( thisList != null ) {
			if ( thisList.data != thatList.data ) { return false; }
			thisList = thisList.next;
			thatList = thatList.next;
		}
		return true;
	}
 
  // Manipulation Procedures 
	// void moveFirst()
	// Makes first element current.
	// Pre: !isEmpty()
	// Post: !offEnd(). 
	void moveFirst () {
		if ( isEmpty() ){ throw new RuntimeException("moveFirst() on empty list"); }
		current = front;
		if ( offEnd() ){ throw new RuntimeException("offEnd() after moveFirst()"); }
	}
	// void moveLast()
	// Makes last element current.
	// Pre: !isEmpty()
	// Post: !offEnd(). 
	void moveLast () {
		if ( isEmpty() ) { throw new RuntimeException("moveLast() on empty list"); }
		current = back;
		if ( offEnd() ) { throw new RuntimeException("offEnd() after moveLast()"); }
	}
	// void moveNext()
	// Steps the current marker toward end of list. 
	// Pre: !isEmpty(), !offEnd(). 
	void moveNext () {
		if ( isEmpty() ) { throw new RuntimeException("moveNext() on empty list"); }
		else if ( offEnd() ) {
			throw new RuntimeException("moveNext() on offEnd list");
		}
		current = current.next;
	}
	// void movePrev()
	// Steps the current marker toward beginning of list. 
	// Pre: !isEmpty(), !offEnd(). 
	void movePrev () {
		if ( isEmpty() ) { throw new RuntimeException("movePrev() on empty list"); }
		else if ( offEnd() ) {
			throw new RuntimeException("movePrev() on offEnd list"); 
		}
		current = current.prev;
	}
	// void insertBeforeFirst(int data)
	// Adds new element to beginning of list. 
	// Post: !isEmpty().
	void insertBeforeFirst (int data) {
		Node n = new Node(data);
		n.next = front;
		if ( front != null ) { front.prev = n; }
		if ( back == null ) { back = n; }
		front = n;
		length = length + 1;
		if ( isEmpty() ) {
			throw new RuntimeException("list isEmpty() after insertBeforeFirst()");
		}
	}
	// void insertAfterLast(int data)
	// Adds new element to end of list. 
	// Post: !isEmpty().
	void insertAfterLast (int data) {
		Node n = new Node(data);
		n.prev = back;
		if ( back != null ) { back.next = n; }
		if ( front == null ) { front = n; } 
		back = n;
		length = length + 1;
		if ( isEmpty() ) {
			throw new RuntimeException("list isEmpty() after insertAfterLast()");
		}
	}
	// void insertBeforeCurrent(int data)
	// Inserts new element just before current. 
	// Pre: !isEmpty(), !offEnd().
	void insertBeforeCurrent (int data) {
		if ( isEmpty() ) {
			throw new RuntimeException("insertBeforeCurrent() on empty list"); 
		} else if ( offEnd() ) {
			throw new RuntimeException("insertBeforeCurrent() on offEnd list"); 
		}
		if ( atFirst() ) { insertBeforeFirst(data); return; }
		Node prevToCurr = current.prev;
		Node n = new Node(data);
		prevToCurr.next = current.prev = n;
		n.prev = prevToCurr;
		n.next = current;
		length = length + 1;
	}
	// void insertAfterCurrent(int data)
	// Inserts new element just after current.
	// Pre: !isEmpty(), !offEnd().
	void insertAfterCurrent (int data) {
		if ( isEmpty() ) {
			throw new RuntimeException("insertAfterCurrent() on empty list"); 
		} else if ( offEnd() ) {
			throw new RuntimeException("insertAfterCurrent() on offEnd list");
		}
		if ( atLast() ) { insertAfterLast(data); return; }
		Node afterCurr = current.next;
		Node n = new Node(data);
		afterCurr.prev = current.next = n;
		n.next = afterCurr;
		n.prev = current;
		length = length + 1;
	}
	// void deleteFirst()
	// Deletes first element.
	// Pre: !isEmpty().
	void deleteFirst () {
		if ( isEmpty() ) {
			throw new RuntimeException("deleteFirst() on empty list"); 
		}
		Node newFirst = front.next;
		if (newFirst == null) { front = current = back = null; length = 0; return; }
		if ( atFirst() ) { current = null; }
		newFirst.prev = null;
		front = newFirst;
		length--;
	}
	// void deleteLast()
	// Deletes last element.
	// Pre: !isEmpty(). 
	void deleteLast () {
		if (isEmpty()) { throw new RuntimeException("deleteLast() on empty list"); }
		Node newLast = back.prev;
		if ( newLast == null ){ front = current = back = null; length = 0; return; }
		if ( atLast() ) { current = null; }
		newLast.next = null;
		back = newLast;
		length--;
	}
	// void deleteCurrent()
	// Deletes current element.  
	// Pre: !isEmpty(), !offEnd()
	// Post: offEnd().
	void deleteCurrent () {
		if ( isEmpty() ) {
			throw new RuntimeException("deleteCurrent() on empty list");
		} else if ( offEnd() ) {
			throw new RuntimeException("deleteCurrent() on offEnd list"); 
		}
		if ( atFirst() ) { deleteFirst(); }
		else if ( atLast() ) { deleteLast(); }
		else {
			Node currPrev = current.prev;
			Node currNext = current.next;
			currPrev.next = currNext;
			currNext.prev = currPrev;
			current = null;
			length--;
		}
		if ( ! offEnd() ) {
			throw new RuntimeException("not offEnd() after deleteCurrent()"); 
		}
	}

  //Other Methods
	// void valid()
	// Checks a number of properties that must be true for this ADT
	// Prints error message and exits if list is bad
	private void valid () {
		int i = 0;
		for ( Node n = front; n != null; n = n.next ) { i++; }
		// Check that length equals number of nodes
		if ( getLength() != i ) {
			throw new RuntimeException( "bad length: " + length + "length, " + i +
				" nodes"); 
		}
		// Check that front points to first node
		if ( !isEmpty() && front.prev != null) {
			throw new RuntimeException( "front.prev != null"); 
		}
		// Check that back points to last node
		if ( !isEmpty() && back.next != null) {
			throw new RuntimeException( "back.next != null"); 
		}
		// Check that all node pointers are null if isEmpty
		if ( isEmpty() ) {
			if ( front != null) {
				throw new RuntimeException( "isEmpty and front != null"); 
			}
			if ( back != null) {
				throw new RuntimeException( "isEmpty and back != null"); 
			}
			if ( current != null) {
				throw new RuntimeException( "isEmpty and current != null"); 
			}
		}
	}
	// List copy()
	// Returns a new List containing the same elements as this list. 
	List copy () {
		List L = new List();
		for( Node n = front; n != null; n = n.next ){ L.insertAfterLast(n.data); }
		return L;
	}
	// List cat(List L)
	// Returns a new list which is the concatenation of this list and the argument
	List cat(List L) {
		List R = new List();
		for( Node n = front; n != null; n = n.next ){ R.insertAfterLast(n.data); }
		for( Node n = L.front; n != null; n = n.next ){ R.insertAfterLast(n.data); }
		return R;
	}
	// void makeEmpty()
	// Set this list to an empty state
	void makeEmpty() { front = current = back = null; length = 0; }
	// public String toString()
	// Overrides Object's toString method.
	public String toString () {
		String s = "";
		for ( Node n = front; n != null; n=n.next ) {
			s = s + n.toString();
			if(n.next != null) { s = s + " "; }
		}
		return s;
	}
	// public static void main(String[] args) // Test driver for the List class. 
	public static void main (String[] args) {
		// Test Lists
		List A = new List();
		List B = new List();
		List C = new List();

		// Testing:
		int num = 101; // This bigger this number, the more nodes will be created
		int i; // counter
		
		// Validity Test
		// See comments for valid()
		A.valid(); B.valid();

		// Add some data
		for( i = 1; i < num; i++ ) {
			A.insertAfterLast(i);
			B.insertBeforeFirst(i);
		}
		A.moveFirst(); B.moveLast();
		for( i = 1; i < num; i++ ) {
			A.insertBeforeCurrent(num-i); A.moveNext();
			B.insertAfterCurrent(num-i); B.movePrev();
		}

		// 1 and 2 test: 
		// move{First,Last,Next,Prev}, get(First,Last,Length), equals
		// insertBefore{First,Current}, insertAfter{Current,Last}
		if ( ! A.equals(B) ) { throw new RuntimeException("Test 1 Failure"); }
		if ((A.getFirst() != B.getLast()) || ( A.getLast() != B.getFirst())) {
			throw new RuntimeException("Test 2 Failure");
		}

		// Move through entire list
		A.moveLast(); B.moveFirst();
		for( i = 1; i < (2*num)-2; i++ ) { A.movePrev(); B.moveNext(); }

		// 3 tests move{Prev,Next}, at{First,Last}
		if ( ! A.atFirst() || ! B.atLast() ) {
			throw new RuntimeException("Test 3 Failure");
		}
		
		// move one more
		A.movePrev();
		B.moveNext();
		// 4 tests offEnd
		if ( ! A.offEnd() || ! B.offEnd() ) {
			throw new RuntimeException("Test 4 Failure");
		}
		
		// Another Validity Test
		A.valid(); B.valid();

		// Move halfway through data
		A.moveFirst(); B.moveLast();
		for( i = 1; i < num; i++ ) { A.moveNext(); B.movePrev(); }
		
		// 5 tests getCurrent
		if (A.getCurrent() != B.getCurrent()) {
			throw new RuntimeException("Test 5 failure");
		}
		
		// Delete current, first, last
		A.deleteCurrent(); A.deleteFirst(); A.deleteLast();
		B.deleteCurrent(); B.deleteFirst(); B.deleteLast();
		
		// 6 tests delete{First,Current,Last}
		if ( ! A.equals(B) ) { throw new RuntimeException("Test 6 Failure"); }

		// Another Validity Test
		A.valid(); B.valid();

		// Move halfway through data
		A.moveFirst(); B.moveLast();
		for( i = 1; i < num-1; i++ ) { A.moveNext(); B.movePrev(); }
		
		// 7 tests getCurrent
		if ( A.getCurrent() != B.getCurrent() ) {
			throw new RuntimeException("Test 7 Failure");
		}
		
		// Make a copy
		C = A.copy();
		// 8 tests copy
		if ( ! C.equals(B) ) { throw new RuntimeException("Test 8 Failure"); }

		// Another Validity Test
		A.valid(); B.valid(); C.valid();

		// make new lists
		A.makeEmpty(); B.makeEmpty(); C.makeEmpty();
		for ( i = 1; i < num; i++ ) {
			A.insertAfterLast(i);
			B.insertAfterLast(i+num-1);
		}
		for ( i = 1; i < 2*num-1; i++ ) { C.insertAfterLast(i); }
		List D = new List();
		D = A.cat(B);
		
		// 9 tests makeEmpty, cat
		if ( ! C.equals(D) ) { throw new RuntimeException("Test 9 Failure"); }

		// One Last Validity Test
		A.valid(); B.valid(); C.valid(); D.valid();

		System.out.println("All List tests passed.");
	}
}
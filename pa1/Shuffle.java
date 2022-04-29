//
//  Shuffle.java
//  
//  Created by Colin Rognlie on 6/29/05.
//  Copyright 2005. All rights reserved.
//
//  Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa1
//

public class Shuffle {
	// Fields
	private List deck = new List();
	private List initdeck = new List();
	private int shuffles;

	// Constructor
	// public Shuffle (int n)
	// tests number of cards, initializes variables
	// shuffles until return to test state
	// prints number of required shuffles
	public Shuffle (int n) {
		if ( n < 1 ) { throw new RuntimeException("Argument is less than 1"); }
		for (int i = 1; i <= n; i++) { deck.insertAfterLast(i); }
		initdeck = deck.copy();
		shuffles = 0;
		// Shuffle until deck returns to initial state
		for( deckShuffle(deck); !deck.equals(initdeck); deckShuffle(deck) ) {}
		// Print number of shuffles
		System.out.println(shuffles);
	}

	// Manipulation Procedure
	// private void deckShuffle(List L)
	// shuffles the deck L according to the given algorithm, increments shuffles
	private void deckShuffle(List L) {
		List A = new List();
		List B = new List();
		// Deal into two half-decks and Shuffle back into one full deck
		while ( !L.isEmpty() ) {
			A.insertAfterLast( L.getFirst() ); L.deleteFirst();
			if ( !L.isEmpty() ) {
				B.insertBeforeFirst( L.getLast() ); L.deleteLast();
			}
		}
		while( !A.isEmpty() || !B.isEmpty() ) {
			if ( !A.isEmpty() ) {	L.insertBeforeFirst(A.getLast()); A.deleteLast();	}
			if ( !B.isEmpty() ) {	L.insertBeforeFirst(B.getLast()); B.deleteLast();	}
		}
		// Increment number of shuffles
		shuffles++;
	}
	
	// Other Procedures
	// public static void main(String[] args)
	// runs Shuffle with command-line argument
	public static void main(String[] args) {
		// new deck with number of cards from command line
		new Shuffle( Integer.parseInt(args[0]) );
	}
}
//
//  Graph.java
//  
//
//  Created by Colin Rognlie on 7/15/05.
//  Copyright 2005. All rights reserved.
//
//  Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa3
//

import java.io.*;
import java.util.StringTokenizer;

public class Graph {
	private List[] adj;
	private int[] dist;
	private int[] parent;
	private int[] color;
	private int numVertex;
	private int numEdge;
	private int source;
	
	// Constructor 
	// Graph(int n) // creates a graph with n vertices and no edges 
	Graph(int n) {
		numEdge = 0;
		numVertex = n;
		source = -1;
		adj    = new List[n+1];
		dist   = new  int[n+1];
		parent = new  int[n+1];
		color  = new  int[n+1];
		for(int i = 1; i <= n; i++) {
			adj[i] = new List();
			dist[i] = -1;
			parent[i] = -1;
			color[i] = -1;
		}
	}
 
	// Access functions 
	// int getParent(int u) // Returns the parent of vertex u. 
	                        // Pre: BFS run on source
	int getParent (int u) { return parent[u]; }
	// int getDist(int u) // Returns the distance from source to u. 
	                      // Pre: BFS run on source
	int getDist (int u) { return dist[u]; }
	// String getPath(int s, int u) // Returns string representation of shortest 
                                  // path from s to u.
	String getPath (int s, int u) {
		if (source != s) { BFS(s); }
		if ( u == s ) {
			return "" + u;
		} else if ( parent[u] == -1 ) {
			return "No path from " + s + " to " + u + " exists";
		} else {
			return getPath(s,parent[u]) + " -> " + u;
		}
	}
 
	// Manipulation procedures 
	// void addEdge(int u, int v) // Inserts new edge joining vertex u to vertex v.
	void addEdge(int u, int v) {
		adj[u].insertAfterLast(v);
		adj[v].insertAfterLast(u);
		source = -1;
	}

	// void BFS(int s) // Runs the BFS algorithm on source vertex s, and sets 
                // distance and parent fields for each vertex in this graph. 
	void BFS (int s) {
		int BLACK = 0;
		int GREY  = 1;
		int WHITE = 2;
		int u,v;
		List L = new List();
		if( s < 1 || s > numVertex ) {
			throw new RuntimeException("Vertex number out of bounds in BFS()");
		}
		for ( int i=1; i <= numVertex; i++ ) {
			color[i] = WHITE;
			dist[i] = parent[i] = -1;
		}
		color[s] = GREY;
		dist[s] = 0;
		parent[s] = -1;
		L.insertAfterLast(s);
		while(!L.isEmpty()) {
			u = L.getFirst(); L.deleteFirst();
			for(adj[u].moveFirst(); !adj[u].offEnd(); adj[u].moveNext()) {
				v = adj[u].getCurrent();
				if ( color[v] == WHITE ) {
					color[v] = GREY;
					dist[v] = dist[u] + 1;
					parent[v] = u;
					L.insertAfterLast(v);
				}
			}
			color[u] = BLACK;
		}
	}
 
	// Other methods 
	// public String toString() //Returns adjacency list representation as a string.
	public String toString() {
		String s = "";
		for(int i=1; i<=numVertex; i++) {
			s = s + i + ": " + adj[i].toString();
			if ( i != numVertex ) { s = s + "\n"; }
		}
		return s;
	}

	// public static void main(String[] args) // Tests Graph ADT. 
	public static void main(String[] args) throws IOException {
		int n,u,v,pDist;
		String outline;
		StringTokenizer st;
		boolean readGraph = false;

		List a = new List();
		List b = new List();

		if(args.length < 1) {throw new RuntimeException("Usage: Graph input_file");}
		BufferedReader in = new BufferedReader(new FileReader(args[0]));

		String line = in.readLine();
		st = new StringTokenizer(line);
		n = Integer.parseInt(st.nextToken());
		Graph g = new Graph(n);

		for(line=in.readLine(); line!=null; line=in.readLine()){
			st = new StringTokenizer(line);
			u = Integer.parseInt(st.nextToken());
			v = Integer.parseInt(st.nextToken());
			if (u == 0 && v == 0) { readGraph = true; } 
			else if ( readGraph ) { a.insertAfterLast(u); b.insertAfterLast(v); }
			else { g.addEdge(u,v); }
		}
		System.out.println(g);
		
		while(!a.isEmpty() && !b.isEmpty()) {
			u = a.getFirst(); v = b.getFirst();
			a.deleteFirst(); b.deleteFirst();
			
			g.BFS(u);
			pDist = g.getDist(v);
			outline = "\nThe distance from " + u + " to " + v + " is ";
			if (pDist == -1) { outline = outline + "infinity.\n" + g.getPath(u,v); }
			else {
				outline = outline + pDist + ".\nA shortest path from "
				          + u + " to " + v + " is: " + g.getPath(u,v);
			}
			System.out.println(outline);
		}
	}
}
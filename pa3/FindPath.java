//
//  FindPath.java
//  
//
//  Created by Colin Rognlie on 7/22/05.
//  Copyright 2005. All rights reserved.
//
//  Colin Rognlie, reflex@cats.ucsc.edu, CMPS101 pa3
//

import java.io.*;
import java.util.StringTokenizer;

public class FindPath {
	// FindPath(in, out)
	FindPath(String inputfile, String outputfile) throws IOException {
		int n,u,v,pDist;
		String fp_out;
		StringTokenizer st;
		boolean readGraph = false;

		List a = new List();
		List b = new List();

		BufferedReader in = new BufferedReader(new FileReader(inputfile));

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
		fp_out = g.toString() + "\n";
		
		while(!a.isEmpty() && !b.isEmpty()) {
			u = a.getFirst(); v = b.getFirst();
			a.deleteFirst(); b.deleteFirst();
			
			g.BFS(u);
			pDist = g.getDist(v);
			fp_out = fp_out + "\nThe distance from " + u + " to " + v + " is ";
			if (pDist == -1) { fp_out = fp_out + "infinity.\n" + g.getPath(u,v); }
			else {
				fp_out = fp_out + pDist + ".\nA shortest path from "
				          + u + " to " + v + " is: " + g.getPath(u,v);
			}
			if(a.getLength() > 0) { fp_out = fp_out + "\n"; }
		}
		PrintWriter out = new PrintWriter(new FileWriter(outputfile)); 
		out.println(fp_out);
    out.close(); 
	}
 
	// public static void main(String[] args) // Executes FindPath on args. 
	public static void main(String[] args) throws IOException {
		if(args.length < 2) {
			throw new RuntimeException("Usage: FindPath input_file output_file");
		}
		new FindPath(args[0],args[1]);
	}
}
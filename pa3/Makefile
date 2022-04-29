# A simple makefile 
FindPath: FindPath.class 
	echo Main-class: FindPath > Manifest 
	jar cvfm FindPath Manifest *.class
	rm Manifest 
	chmod +x FindPath 

FindPath.class: FindPath.java Graph.class List.class
	javac -Xlint FindPath.java 

Graph.class: Graph.java List.class
	javac -Xlint Graph.java

List.class: List.java
	javac -Xlint List.java

clean: 
	rm -f *.class FindPath 

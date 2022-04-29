# Makefile for Graph ADT and related modules. 
# make               makes FindComponents 
# make GraphClient   makes GraphClient 
# make ListClient    makes ListClient 
# make clean         removes all object and executable files 

FindComponents : FindComponents.o Graph.o List.o 
	gcc -o FindComponents FindComponents.o Graph.o List.o 

GraphClient : GraphClient.o Graph.o List.o 
	gcc -o GraphClient GraphClient.o Graph.o List.o 

ListClient : ListClient.o List.o 
	gcc -o ListClient ListClient.o List.o 

FindComponents.o : FindComponents.c Graph.h List.h 
	gcc -c -ansi -Wall FindComponents.c 

GraphClient.o : GraphClient.c Graph.h List.h 
	gcc -c -ansi -Wall GraphClient.c 

ListClient.o : ListClient.c List.h 
	gcc -c -ansi -Wall ListClient.c 

Graph.o : Graph.c Graph.h List.h List.o
	gcc -c -ansi -Wall Graph.c 

List.o : List.c List.h 
	gcc -c -ansi -Wall List.c 

clean : 
	rm -f FindComponents GraphClient ListClient Graph FindComponents.o GraphClient.o ListClient.o Graph.o List.o out_file outfile

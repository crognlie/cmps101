# Makefile for Graph ADT and related modules. 
# make                          makes MST 
# make GraphClient              makes GraphClient 
# make ListClient               makes ListClient 
# make PriorityQueueClient      makes PriorityQueueClient 
# make clean                    removes all object and executable files 

MST : MST.o Graph.o List.o PriorityQueue.o 
	gcc -o MST MST.o Graph.o List.o PriorityQueue.o 

GraphClient : GraphClient.o Graph.o List.o PriorityQueue.o 
	gcc -o GraphClient GraphClient.o Graph.o List.o PriorityQueue.o 

ListClient : ListClient.o List.o 
	gcc -o ListClient ListClient.o List.o 

PriorityQueueClient : PriorityQueueClient.o PriorityQueue.o 
	gcc -o PriorityQueueClient PriorityQueueClient.o PriorityQueue.o 

MST.o : MST.c Graph.h  
	gcc -c -ansi -Wall MST.c 

GraphClient.o : GraphClient.c Graph.h 
	gcc -c -ansi -Wall GraphClient.c 

ListClient.o : ListClient.c List.h 
	gcc -c -ansi -Wall ListClient.c 

PriorityQueueClient.o : PriorityQueueClient.c PriorityQueue.h 
	gcc -c -ansi -Wall PriorityQueueClient.c 

Graph.o : Graph.c Graph.h List.h PriorityQueue.h 
	gcc -c -ansi -Wall Graph.c 

List.o : List.c List.h 
	gcc -c -ansi -Wall List.c 

PriorityQueue.o : PriorityQueue.c PriorityQueue.h 
	gcc -c -ansi -Wall PriorityQueue.c 

clean : 
	rm -f MST GraphClient ListClient PriorityQueueClient MST.o GraphClient.o ListClient.o PriorityQueueClient.o Graph.o List.o PriorityQueue.o outfile

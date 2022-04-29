# Colin Rognlie
# reflex@cats.ucsc.edu
# Makefile for Programming Assignment 2 
# CMPS 101 Summer 2005  
 
Shuffle : List.o Shuffle.o
	gcc -o Shuffle Shuffle.o List.o 
 
Shuffle.o : List.h Shuffle.c
	gcc -c -ansi -Wall Shuffle.c 
 
ListClient: List.o ListClient.o
	gcc -o ListClient ListClient.o List.o 
 
ListClient.o : List.h ListClient.c
	gcc -c -ansi -Wall ListClient.c 
 
List.o : List.h List.c
	gcc -c -ansi -Wall List.c 
 
clean :
	rm -f Shuffle ListClient Shuffle.o ListClient.o List.o

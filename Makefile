project: cut.o get.o
	cc cut.o get.o -Wall -o project
get.o: get.c header.h
	cc -c get.c -Wall
cut.o: cut.c header.h
	cc -c cut.c -Wall


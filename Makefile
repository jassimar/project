project: cut.o extrafunctions.o
	cc cut.o extrafunctions.o -Wall -o project
extrafunctions.o: extrafunctions.c header.h
	cc -c extrafunctions.c -Wall
cut.o: cut.c header.h
	cc -c cut.c -Wall


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TYPE1 1
#define TYPE2 2
#define YES 1
#define NO 0

/*This program uses only one data structure. This is to store all the arguments given by the user in the command line */

typedef struct arguments {
	char type;
	int j; /* to tell if -c1 or -c 1 i.e. if there is spacing between the arguments */
	int where; /* To tell at which index the option is */
	int complement; /* To mention if the --complement is there */
	int delim_surpress; /* To mention if the -s option is there */
	char filename[20]; 
	int changedelimcheck; /* If the user wants to change the output delim, i.e. --output-delimeter=STRING option */
	char changedelim[10]; /* The string to which it changes */
	char delim; /* This is if the user wants to enter his own delimeter. The default is '\t' */ 
}arguments;

arguments get(int argc, char *argv[]); /* This function is to retrieve all the command line arguments and store it. The stored data is used for the program */

int errorcheck(int argc, char **argv);

void help();



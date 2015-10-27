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
typedef struct arguments {
	char type;
	int j; /* to tell if -c1 or -c 1 i.e. if there is spacing between the arguments */
	int where; /* To tell at which index the option is */
	int complement; /* To mention if the --complement is there */
	char filename[20];
	char delim;
}arguments;
arguments get(int argc, char *argv[]);
int errorcheck(int argc, char **argv);

#define TYPE1 1
#define TYPE2 2
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct arguments {
	char type;
	int j; // to tell if -c1 or -c 1
	int where; //To tell at which index the option is
	char filename[20];
	char delim;
}arguments;
arguments get(int argc, char *argv[]);

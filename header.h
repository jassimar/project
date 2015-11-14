/* cut - remove parts of lines of files.
   Copyright (C) 2015  jassim.15@gmail.com Jassim AR..

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

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
	char type; /* To tell if it is -f, -c, -b, or -l */
	int j; /* to tell if -c1 or -c 1 i.e. if there is spacing between the arguments */
	int where; /* To tell at which index of the command line arguments the option is */
	int complement; /* To mention if the --complement is there */
	int delim_surpress; /* To mention if the -s option is there */
	char filename[20]; /* Name of the file from which we are cutting */
	int changedelimcheck; /* If the user wants to change the output delim, i.e. "--output-delimeter=STRING" option */
	char changedelim[10]; /* The string to which it changes */
	char delim; /* This is if the user wants to enter his own delimeter. The default is '\t' */ 
}arguments;

arguments get(int argc, char *argv[]); /* This function is to retrieve all the command line arguments and store it. The stored data is used for the program */

int errorcheck(int argc, char **argv); /* Function to check for errors */

void help();



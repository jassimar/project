#include "header.h"
/* extrafunctions.c
   (Part of the 'cut' function - remove parts of lines of files.)
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

arguments get(int argc, char *argv[]) {
	int i = 1, j, k;
	arguments a;
	a.delim = '\0';
	a.changedelimcheck = NO;
	a.complement = NO;
	a.delim_surpress = NO;
	while(i < argc) {
		if(argv[i][0] == '-' && argv[i][1] != '-') {
			if(argv[i][1] != 'd' && argv[i][1] != 's' ) {
				a.type = argv[i][1];
				a.where = i;
				if(argv[i][2] == '\0') {
					i++; /* This is done so that the loop skips the next commandline argument */
					a.j = TYPE2;
				}
				else
					a.j = TYPE1;
			}
			else if(argv[i][1] == 'd'){
				if(argv[i][2] != '\0') 
					a.delim = argv[i][2];
				else {
					a.delim = argv[i + 1][0];
					i++;
				}
			}
			else /* -s option */
				a.delim_surpress = YES;
			
		}
		else if(argv[i][1] == '-') {
			if(argv[i][2] == 'c') /* For the --complement option */
				a.complement = YES;
			else if(argv[i][2] == 'h') {
				help();
				exit(1);
			}
			else if(argv[i][2] == 'o') { /*--output-delimiter option */
				a.changedelimcheck = YES;
				j = 19;
				k = 0;
				while(argv[i][j] != '\0') {
					a.changedelim[k] = argv[i][j];
					k++;
					j++;
				}
				a.changedelim[k] = '\0';
				
			}
		}

		else
			strcpy(a.filename, argv[i]);
		
		i++;
	}
	
	return a;
}
/* The errors :
1. -f 2-1, Decreasing range
2. -f 0-1, numbering starts from 1
3. -d ::, multiple delimiters
4. delimeter cannot be used for -c and -b
5. invalid byte, character or field list
6. delim surpress for something other than -f
*/		
int errorcheck(int argc, char **argv) {
	int i = 1, j, k, delim = 0, delim_surpress = 0;
	char type;
	while(i < argc) {
		if(argv[i][0] == '-' && argv[i][1] != '-') {
			if(argv[i][1] != 'd' && argv[i][1] != 's') {
				type = argv[i][1];
				
				if(argv[i][2] == '\0') {
					j = ++i;
					k = 0;
				}
				else {
					j = i;
					k = 2;
				}
				if(atoi(&argv[j][k]) == 0 && argv[j][k] != 'c') {
					printf("Error: Numbering starts from 1\n");
					return 1;
				}
				if(argv[j][k + 1] == '-' && argv[j][k + 2] != '\0') {
					if(atoi(&argv[j][k]) > atoi(&argv[j][k + 2])) {
						printf("Error: Decreasing range\n");
						return 1;
					}
				} 
			}
			else if(argv[i][1] == 'd') 
				delim = 1;
				 
			else if(argv[i][1] == 's')
				delim_surpress = 1;
		
		}
		if(argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'o') {
			if(argv[i][18] != '=') { /* Spelling of --output-delimiter may be wrong */
				printf("There is no option as such!\n");
				return 1;
			}
		}

		if(delim  && type != 'f') {
			printf("Error: Delimeter can only be used for fields\n");
			return 1;
		}
		if(delim_surpress && type != 'f') {
			printf("Error: Delimiter surpressing only makes sense when fields are being cut!\n");
			return 1;
		}
		/*else
			strcpy(a.filename, argv[i]); */
		
		i++;
		
	}	
	return 0;
}

void help() {

printf("Usage: ./project OPTION... [FILE]...\n");
printf("Print selected parts of lines from each FILE to standard output.\n\n");

printf("Mandatory arguments to long options are mandatory for short options too.\n");
printf("  -b,                     select only these bytes\n");
printf("  -c,                     select only these characters\n");
printf("  -d,                     use DELIM instead of TAB for field delimiter\n");
printf("  -f,                     select only these fields;  also print any line\n");
printf("                            that contains no delimiter character, unless\n");
printf("                            the -s option is specified\n");
printf("  -l		          select only these lines(Not availiable in the 'cut' function)\n");
printf("  -n                      (ignored)\n");
printf("      --complement        complement the set of selected bytes, characters\n");
printf("                            or fields\n");
printf("  -s, --only-delimited    do not print lines not containing delimiters\n");
printf("      --output-delimiter=STRING  use STRING as the output delimiter\n");
printf("                            the default is to use the input delimiter\n");
printf("      --help     display this help and exit\n\n");

printf("Use one, and only one of -b, -c or -f.  Each LIST is made up of one\n");
printf("range, or many ranges separated by commas.  Selected input is written\n");
printf("in the same order that it is read, and is written exactly once.\n");
printf("Each range is one of:\n\n");

printf("  N     N'th byte, character or field, counted from 1\n");
printf("  N-    from N'th byte, character or field, to end of line\n");
printf("  N-M   from N'th to M'th (included) byte, character or field\n");
printf("  -M    from first to M'th (included) byte, character or field\n\n");

printf("With no FILE, or when FILE is -, read standard input.\n");

printf("Report bugs of this program to jassim.15@gmail.com\n");


}	

		
			
				

	

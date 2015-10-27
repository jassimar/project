#include "header.h"
arguments get(int argc, char *argv[]) {
	int i = 1;
	arguments a;
	a.delim = '\0';
	a.complement = NO;
	while(i < argc) {
		if(argv[i][0] == '-' && argv[i][1] != '-') {
			if(argv[i][1] != 'd' ) {
				a.type = argv[i][1];
				a.where = i;
				if(argv[i][2] == '\0') {
					i++; /* This is done so that the loop skips the next commandline argument */
					a.j = TYPE2;
				}
				else
					a.j = TYPE1;
			}
			else {
				if(argv[i][2] != '\0') 
					a.delim = argv[i][2];
				else {
					a.delim = argv[i + 1][0];
					i++;
				}
			}
			
		
		}
		else if(argv[i][1] == '-' && argv[i][2] == 'c') /* For the --complement option */
				a.complement = YES;

		else
			strcpy(a.filename, argv[i]);
		
		i++;
	}
	
	return a;
}
/* The errors :
1. -f 2-1, Decreasing range
2. -f 0-1, numbering starts from 1
3. -d ::, multiple delimeters
4. delimeter cannot be used for -c and -b
5. invalid byte, character or field list
*/		
int errorcheck(int argc, char **argv) {
	int i = 1, j, k, delim = 0;
	char type;
	while(i < argc) {
		if(argv[i][0] == '-') {
			if(argv[i][1] != 'd') {
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
			else 
				delim = 1;
		
		}
		if(delim && type != 'f') {
			printf("Error: Delimeter can only be used for fields\n");
			return 1;
		}
		/*else
			strcpy(a.filename, argv[i]); */
		
		i++;
		
	}	
	return 0;
}



		
			
				

	

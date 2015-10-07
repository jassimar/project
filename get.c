#include "header.h"
arguments get(int argc, char *argv[]) {
	int i = 1;
	arguments a;
	a.delim = '\0';
	
	while(i < argc) {
		if(argv[i][0] == '-') {
			if(argv[i][1] != 'd') {
				a.type = argv[i][1];
				a.where = i;
				if(argv[i][2] == '\0') {
					i++; /*This is done so that the loop skips the next commandline argument */
					a.j = TYPE2;
				}
				else
					a.j = TYPE1;
			}
			else {
				if(argv[i][2] != '\0') 
					a.delim = argv[i][2];
				else {
					a.delim = argv[i+1][0];
					i++;
				}
			}
		
		}
		else
			strcpy(a.filename, argv[i]);
		
		i++;
	}
	
	return a;
}
		
			
			
				

	

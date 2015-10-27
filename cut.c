#include "header.h"
int main(int argc, char *argv[]) {
	
	arguments a;
	char c, delim;
	int fd, i, j, x;
	a = get(argc, argv);
	fd = open(a.filename, O_RDONLY);
	if(fd == -1) {
		perror("Error");
		return 1;
	}
	int error;
	error = errorcheck(argc, argv);
	if(error)
		exit(1);

	if(a.j == TYPE1) {
		i = a.where;
		j = 2;
	}
	else {
		i = a.where + 1;
		j = 0;
	}
	if(a.complement == NO) { /* This means the complement option is not mentioned */
		switch(a.type) {
			case 'b' :
			case 'c' :
					
				while(read(fd, &c, 1)) {
					static int count = 1;
					
					if(argv[i][j] == '-') { //For cases like -c-2
						if(count <= atoi(&argv[i][j + 1]) && c != '\n'	)
							printf("%c", c);
								
					}
					else if(count == atoi(&argv[i][j])) {
						printf("%c", c);
						if(argv[i][j + 1] == '-') {
							if(argv[i][j + 2] == '\0') { //For cases like -c1-
								while(c != '\n') {
									read(fd, &c, 1);
									printf("%c", c);
									
									
									}
							}
							else { //For cases like -c1-5
								x = count;
								while(x < atoi(&argv[i][j + 2]) && c != '\n') {
									read(fd, &c, 1);
									printf("%c", c);
									x++;
								}
								if(c == '\n') {
									count = 1;
									continue;
								}
							//printf("\n");
							}	
							
						}
					}
	
							
					count++;
					if(c == '\n') {
						if(argv[i][j + 1] != '-' || argv[i][j + 2] != '\0')
							printf("\n");
						count = 1;
					}
					
						
					
				}	
				break;
			case 'f' :
				if(a.delim == '\0')
					delim = '\t';
				else
					delim = a.delim;
				while(read(fd, &c, 1)) {
					static int count = 1;
					if(argv[i][j] == '-') {
						if(count <= atoi(&argv[i][j + 1]) && c != '\n')
							printf("%c", c);
						
					}
					if(count == atoi(&argv[i][j])) {
						while(c != delim && c != '\n') {
							printf("%c", c);
			
							read(fd, &c, 1);
						
						}
					/* This is incase the user has entered a number more than the number of columns in the file */ 	
						if(c == '\n') 
							goto here;
						if(argv[i][j + 1] == '-') {
							if(argv[i][j + 2] == '\0') {
								while(c != '\n') {
									printf("%c", c);
									read(fd, &c, 1);
							
								}
							}
							else {
								x = count;
								printf("%c", c);
								while(x < atoi(&argv[i][j + 2]) && (read(fd, &c, 1)) != -1) {
									if(c == '\n') 											break;
									printf("%c", c);
									//read(fd, &c, 1);
							
									if(c == delim)
										x++;
								}
							
							}	
					
						}
				
					}
					if(c == delim)	
						count++;
					here:
					if(c == '\n') {
						printf("\n");
						count = 1;
					}
			
				
			
				}
				break;
		}
	}
	else if(a.complement == YES) {
		switch(a.type) {
			case 'b' :
			case 'c' :
				
				while(read(fd, &c, 1)) {
					static int count = 1;
					
					if(argv[i][j] == '-') { //For cases like -c-2
						if(count <= atoi(&argv[i][j + 1]) && c != '\n') {
							count++;
							continue;
						}
							//printf("%c", c);
								
					}
					else if(count == atoi(&argv[i][j])) {
						//printf("%c", c);
						if(argv[i][j + 1] != '-') {
							count++;
							continue;
						}
						else {
							if(argv[i][j + 2] == '\0') { //For cases like -c1-
								while(c != '\n') {
									read(fd, &c, 1);
									//printf("%c", c);
									
									
								}
							}
							else { //For cases like -c1-5
								x = count;
								while(x < atoi(&argv[i][j + 2]) && c != '\n') {
									read(fd, &c, 1);
									//printf("%c", c);
									x++;
								}
								count++;
								if(c == '\n') {
									printf("\n");
									count = 1;
									
								}
								
								continue;
							//printf("\n");
							}	
							
						}
					}
		
					printf("%c", c);	
					count++;
					if(c == '\n') {
						//if(argv[i][j + 1] != '-' || argv[i][j + 2] != '\0')
						//	printf("\n");
						count = 1;
					}
					
							
				
				}	
				break;
			case 'f' :
				
				if(a.delim == '\0')
					delim = '\t';
				else
					delim = a.delim;
				while(read(fd, &c, 1)) {
					static int count = 1;
					if(argv[i][j] == '-') { //-f-2
						if(count <= atoi(&argv[i][j + 1]) && c != '\n') {
							if(c == delim)
								count++;
							continue;
							//printf("%c", c);
						}
					
					}
					if(count == atoi(&argv[i][j])) { 
						while(c != delim && c != '\n') {
							//printf("%c", c);
							read(fd, &c, 1);
						
						}
						
						if(argv[i][j + 1] == '-') { 
							if(argv[i][j + 2] == '\0') { //-f1-
								while(c != '\n') {
									//printf("%c", c);
									read(fd, &c, 1);
							
								}
							}
							else { //-f1-3
								x = count;
								//printf("%c", c);
								while(x < atoi(&argv[i][j + 2]) && c != '\n' && (read(fd, &c, 1)) != -1) {
									//printf("%c", c);
									//read(fd, &c, 1);
							
									if(c == delim)
										x++;
								}
							//printf("\n");
							}	
					
						}
						if(c == delim) {
							count++;
							continue;
						}
				
					}	
					printf("%c", c);
					if(c == delim)	
						count++;
					if(c == '\n') {
						//printf("\n");
						count = 1;
					}	
			
				
			
				}	
				break;
			}	
	}			
	return 0;		
}		

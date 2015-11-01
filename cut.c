#include "header.h"
/* cut -- A function replicating the LINUX command 'cut'.
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

int main(int argc, char *argv[]) {
	
	arguments a;
	char c, delim;
	int i, j, x, check;
	a = get(argc, argv);
	//printf("%s", a.filename);
	FILE *fp;
	fp = fopen(a.filename, "r");
	long bytes;
	char delim2[10];
	if(a.changedelimcheck)
		strcpy(delim2, a.changedelim);
	if(fp == NULL) {
		perror("Error");
		return 1;
	}
	int error;
	error = errorcheck(argc, argv);
	if(error) {
		printf("Try './project --help' for more information.\n");
		exit(1);
	}
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
					
				while(fscanf(fp, "%c", &c) != EOF) {
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
									fscanf(fp, "%c", &c);
									printf("%c", c);
									
									
								}
							}
							else { //For cases like -c1-5
								x = count;
								while(x < atoi(&argv[i][j + 2]) && c != '\n') {
									fscanf(fp, "%c", &c);
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
				
				while(fscanf(fp, "%c", &c) != EOF) {
					static int count = 1;
					if(count == 1 && a.delim_surpress == YES) {/* This loop will check if the line contains a delimeter.*/
						check = 0;
						bytes = ftell(fp);
						
						while(c != '\n') {
							fscanf(fp, "%c", &c);
							if(c == delim)
								check++;
						}
						
						if(check != 0) {
							//printf("%lu  ", bytes);
							fseek(fp, bytes - 1, SEEK_SET);
							fscanf(fp, "%c", &c);
							
						}
						else 
							continue;
					} 
							
					if(argv[i][j] == '-') {
						if(count <= atoi(&argv[i][j + 1]) && c != '\n') {
							if(c == delim && a.changedelimcheck)
								printf("%s", delim2);
							else
								printf("%c", c);
						}
					}
					if(count == atoi(&argv[i][j])) {
						while(c != delim && c != '\n') {
							printf("%c", c);
			
							fscanf(fp, "%c", &c);
						
						}
					/* This is incase the user has entered a number more than the number of columns in the file */ 	
						if(c == '\n') 
							goto here;
						if(argv[i][j + 1] == '-') {
							if(argv[i][j + 2] == '\0') {
								while(c != '\n') {
									if(c == delim && a.changedelimcheck)
										printf("%s", delim2);
									else
										printf("%c", c);
									fscanf(fp, "%c", &c);
							
								}
							}
							else {
								x = count;
								if(a.changedelimcheck)
									printf("%s", delim2);
								else
									printf("%c", c);
								while(x < atoi(&argv[i][j + 2]) && fscanf(fp, "%c", &c) != EOF) {
									if(c == '\n') 											break;
									if(c == delim) {
										x++;
										
									}
									if(c == delim && a.changedelimcheck)
										printf("%s", delim2);		
									else
										printf("%c", c);
									//read(fd, &c, 1);
							
									
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
				
				while(fscanf(fp, "%c", &c) != EOF) {
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
									fscanf(fp, "%c", &c);
									//printf("%c", c);
									
									
								}
							}
							else { //For cases like -c1-5
								x = count;
								while(x < atoi(&argv[i][j + 2]) && c != '\n') {
									fscanf(fp, "%c", &c);
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
				
				while(fscanf(fp, "%c", &c) != EOF) {
					static int count = 1;
					if(count == 1 && a.delim_surpress == YES) {
						check = 0;
						bytes = ftell(fp);
						
						while(c != '\n') {
							fscanf(fp, "%c", &c);
							if(c == delim)
								check++;
						}
						
						if(check != 0) {
							//printf("%lu  ", bytes);
							fseek(fp, bytes - 1, SEEK_SET);
							fscanf(fp, "%c", &c);
							
						}
						else 
							continue;
					}
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
							fscanf(fp, "%c", &c);
						
						}
						
						if(argv[i][j + 1] == '-') { 
							if(argv[i][j + 2] == '\0') { //-f1-
								while(c != '\n') {
									//printf("%c", c);
									fscanf(fp, "%c", &c);
							
								}
							}
							else { //-f1-3
								x = count;
								//printf("%c", c);
								while(x < atoi(&argv[i][j + 2]) && c != '\n' && fscanf(fp, "%c", &c) != EOF) {
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
					if(c == delim && a.changedelimcheck)
						printf("%s", delim2);
					else	
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

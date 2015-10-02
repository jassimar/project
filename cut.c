
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fd, x; char c;
	fd = open(argv[2], O_RDONLY);
	if(argv[1][1] == 'c') {
		while(read(fd, &c, 1)) {
			static int count = 1;
			if(argv[1][2] == '-') { //For cases like -c-2
				if(count <= atoi(&argv[1][3])){
					
					printf("%c", c);
				}
						
			}
			else if(count == atoi(&argv[1][2])) {
				printf("%c", c);
				if(argv[1][3] == '-') {
					if(argv[1][4] == '\0') { //For cases like -c1-
						while(c != '\n') {
							read(fd, &c, 1);
							printf("%c", c);
							
							
						}
					}
					else { //For cases like -c1-5
						x = count;
						while(x < atoi(&argv[1][4])) {
							read(fd, &c, 1);
							printf("%c", c);
							x++;
						}
					//printf("\n");
					}	
					
				}
			}
				
			count++;
			if(c == '\n') {
				if(argv[1][3] != '-' || argv[1][4] != '\0')
					printf("\n");
				count = 1;
			}
			
				
			
		}	
	
	}
	if(argv[1][1] == 'f') {
		while(read(fd, &c, 1)) {
			static int count = 1;
			if(argv[1][2] == '-') {
				if(count <= atoi(&argv[1][3])){
					
					printf("%c", c);
				}
						
			}
			if(count == atoi(&argv[1][2])) {
				while(c != '\t') {
					printf("%c", c);
			
					read(fd, &c, 1);
						
				}
				if(argv[1][3] == '-') {
					if(argv[1][4] == '\0') {
						while(c != '\n') {
							printf("%c", c);
							read(fd, &c, 1);
							
						}
					}
					else {
						x = count;
						while(x < atoi(&argv[1][4])) {
							printf("%c", c);
							read(fd, &c, 1);
							
							if(c == '\t')
								x++;
						}
					//printf("\n");
					}	
					
				}
			
			}
			if(c == '\t')	
				count++;
			if(c == '\n') {
				printf("\n");
				count = 1;
			}
			
				
			
		}
	}			
	return 0;		

}

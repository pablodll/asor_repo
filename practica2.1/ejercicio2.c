#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(){ 	
	if(setuid(0) == -1){
		perror("Error");
		fprintf(stderr, "ERRNO: %d\n", errno);
		fprintf(stderr, "Error string: %s\n", strerror(errno));	 
	}
   	return 1;
}

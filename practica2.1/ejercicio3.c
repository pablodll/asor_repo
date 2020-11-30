#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(){
   int i = 1;
   for(i; i <= 255; i++){
   	fprintf(stderr, "Error %d: %s\n", i, strerror(i));	
   }
   
   return 1;
}

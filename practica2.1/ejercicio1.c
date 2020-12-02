#include <stdio.h>
#include <sys/types.h>
#include <errno.h>

int main(){
   
   if(setuid(0) == -1){
      perror("Error"); 
   }

   return 0;
}

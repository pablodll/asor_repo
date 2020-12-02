#include <stdio.h>
#include <time.h>

int main(){
    time_t t;

    if(time(&t) == (time_t)-1){
        perror("ERROR");
    }
    else{
        printf("%d\n", t);
    }
    
    return 0;
}
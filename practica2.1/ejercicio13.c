#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(){
    int i;
    struct timeval tv1;
    struct timeval tv2;

    if(gettimeofday(&tv1, NULL) == -1){
        perror("ERROR");
    }
    else{
        for(i = 0; i < 1000000; i++);

        if(gettimeofday(&tv2, NULL) == -1){
            perror("ERROR");
        }
        else{
            printf("Tiempo transcurrido (ms): %ld\n", tv2.tv_usec - tv1.tv_usec);
        }
    }

    return 1;
}
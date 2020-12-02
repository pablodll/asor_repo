#include <stdio.h>
#include <time.h>

int main(){
    struct tm *localt;
    time_t t;

    if(time(&t) == (time_t)-1){
        perror("ERROR");
    }
    else{
        localt = localtime(&t);
        if(localt != NULL){
            printf("Año: %d\n", 1900 + localt->tm_year);
        } 
        else{
            perror("ERROR");
        }
    }

    return 0;
}
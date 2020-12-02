#include <stdio.h>
#include <time.h>
#include <locale.h>

int main(){
    struct tm *localt;
    time_t t;

    char s[200];
    
    setlocale(LC_ALL, "es_ES");

    if(time(&t) == (time_t)-1){
        perror("ERROR");
    }
    else{
        localt = localtime(&t);
        if(localt != NULL){
            if(strftime(s, sizeof(s), "%A, %e de %B de %Y, %H:%M", localt) == 0){
                fprintf(stderr, "strftime returned 0\n");
            }
            else{
                printf("%s\n", s);
            }
        } 
        else{
            perror("ERROR");
        }
    }

    return 0;
}
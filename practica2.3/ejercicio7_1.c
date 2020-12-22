#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    
    pid_t pid = fork();
    int stat;

    if(pid == -1){
        perror("fork error");
    }
    else if(pid == 0){ // HIJO
        if(system(argv[1]) == -1){
            perror("system error");
            exit(1);
        }
        exit(0);
    }
    else if(pid > 0){ // PADRE
        if(wait(&stat) == -1){
            perror("wait error");
        }
        
        if(WIFEXITED(stat) && WEXITSTATUS(stat) == 0){
            printf("El comando termino de ejecutarse\n"); 
        }
    }

    return 0;
}
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    int fd[2];

    if(pipe(fd) == -1){
        perror("Error creating pipe");
    }

    pid_t pid = fork();

    if(pid == 0){ // HIJO

        char *args[] = {argv[3], argv[4], NULL};

        if(dup2(fd[0], 0) == -1){
            perror("Child dup error");
        }

        if(close(fd[0]) == -1 || close(fd[1]) == -1){
            perror("Child close error");
        }

        if(execvp(argv[3], args) == -1){
            perror("Child execvp error");
        }
    }
    else if(pid > 0){ // PADRE
        
        char *args[] = {argv[1], argv[2], NULL};

        if(dup2(fd[1], 1) == -1){
            perror("Parent dup error");
        }

        if(close(fd[0]) == -1 || close(fd[1]) == -1){
            perror("Parent close error");
        }

        if(execvp(argv[1], args) == -1){
            perror("Parect execvp error");
        }
    }
    else{
        perror("Fork error");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    pid_t pid = fork();

    if(pid == 0) { // HIJO
        pid_t sid = setsid(); // Nueva sesion

        if(sid == -1){
            perror("setsid error");
        }

        chdir("/tmp"); // Cambiar directorio

        int fd1 = open("/tmp/daemon.out", O_RDWR | O_CREAT | O_TRUNC, 0666);
        int fd2 = open("/tmp/daemon.err", O_RDWR | O_CREAT | O_TRUNC, 0666);
        int fd0 = open ("/dev/null", O_RDWR);

        if(dup2(fd1, 1) == -1){ // stdout
            perror("dup stdout error");
        }
        if(dup2(fd2, 2) == -1){ // stderr
            perror("dup stderr error");
        }
        if(dup2(fd0, 0) == -1){ // stdin
            perror("dup stdin error");
        }

        sleep(5); // Dormir hijo (demonio) para que padre acabe antes

        if(execvp(argv[1], argv+1) == -1){
            perror("execvp error");
            exit(1);
        }
        exit(0);
    }
    else if(pid > 0) { // PADRE
        // sleep(5); // Dormir padre para que hijo acabe antes
    }
    else {
        perror("fork error");
        return -1;
    }

    return 0;
}
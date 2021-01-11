#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    
    fd_set rfds;
    int retval;
    char buf[256];

    int fd1 = open("pipe1", O_RDONLY | O_NONBLOCK);
    int fd2 = open("pipe2", O_RDONLY | O_NONBLOCK);

    int maxfd = fd1 > fd2 ? fd1 : fd2;

    if(fd1 == -1){
        perror("pipe1 open error");
    }
    if(fd2 == -1){
        perror("pipe2 open error");
    }

    FD_ZERO(&rfds);
    FD_SET(fd1, &rfds);
    FD_SET(fd2, &rfds);

    while(1){
        retval = select(maxfd + 1, &rfds, NULL, NULL, NULL);

        if(retval == -1){
            perror("select error");
        }
        else if(retval){

            if(FD_ISSET(fd1, &rfds)){
                retval = read(fd1, buf, sizeof(buf));

                if(retval == -1){ // Error
                    perror("fd1 read error");
                }

                else if (retval == 0){ // Fin del fichero (cerrar y volver a abrir) 
                    if(close(fd1) == -1){
                        perror("pipe1 close error");
                    }

                    fd1 = open("pipe1", O_RDONLY | O_NONBLOCK);
                }

                else{ // Leer
                    printf("Leido de pipe1: %s\n", buf);
                }
            }
            else if(FD_ISSET(fd2, &rfds)){
                retval = read(fd2, buf, sizeof(buf));

                if(retval == -1){ // Error
                    perror("fd2 read error");
                }

                else if (retval == 0){ // Fin del fichero (cerrar y volver a abrir) 
                    if(close(fd2) == -1){
                        perror("pipe2 close error");
                    }

                    fd2 = open("pipe2", O_RDONLY | O_NONBLOCK);
                }

                else{ // Leer
                    printf("Leido de pipe2: %s\n", buf);
                }
            }
        }
    }

    return 0;
}
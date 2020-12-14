#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[]){

    int fd = open(argv[1], O_RDWR);
    if(fd == -1){
        perror("open error");
    }

    if(lockf(fd, F_TEST, 0) == 0){
        printf("Desbloqueado o bloqueado por este proceso\n");

        if(lockf(fd, F_LOCK, 0) == -1){
            perror("lock error");
        }
        else{
            time_t t = time(0);
            struct tm *lt = localtime(&t);

            // Escribir hora por consola
            printf("Hora %d:%d\n", lt->tm_hour, lt->tm_min);

            // Escribir hora en fichero
            FILE *f = fdopen(fd, "w+");
            fprintf(f, "Hora %d:%d\n", lt->tm_hour, lt->tm_min);

            sleep(3);

            if(lockf(fd, F_ULOCK, 0) == -1){
                perror("unlock error");
            }
        }
    }
    else{
        printf("Bloqueado por otro proceso\n");
        return 0;
    }

    return 0;
}
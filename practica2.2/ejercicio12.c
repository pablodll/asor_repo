#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    
    int fd = open(argv[1], O_RDWR | O_CREAT, 0700);
    if(fd == -1){
        perror("open error");
    }

    if(dup2(fd, 1) == -1){
        perror("dup error");
    }

    printf("Prueba 1\n");
    printf("Prueba 2\n");
    printf("Prueba 3\n");

    return 0;
}
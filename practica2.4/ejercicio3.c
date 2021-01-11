#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    int pipe = open("pipe", O_WRONLY);

    if(pipe == -1){
        perror("open error");
        _exit(0);
    }

    printf("%d\n", sizeof(argv[1]));

    if(write(pipe, argv[1], strlen(argv[1])) == -1){
        perror("write error");
    }

    return 0;
}
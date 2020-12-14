#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    struct stat buf;
    if(stat(argv[1], &buf) == -1){
        perror("stat error");
    }

    if(S_ISREG(buf.st_mode)) {
        char hlink[30];
        char slink[30];
        strcat(strcpy(hlink, argv[1]), ".hard");
        strcat(strcpy(slink, argv[1]), ".sym");

        if(link(argv[1], hlink) == -1){
            perror("hard link error");
        }
        if(symlink(argv[1], slink) == -1){
            perror("symbolic link error");
        }
    }

    return 0;
}
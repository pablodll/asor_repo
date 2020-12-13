#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]){
    
    struct stat buf;

    if(stat(argv[1], &buf) == -1){
        perror("error");
    }
    
    printf("major: %d, minor: %d\n", major(buf.st_dev), minor(buf.st_dev));
    printf("i-node: %d\n", buf.st_ino);
    
    // Determinar tipo
    if(S_ISLNK(buf.st_mode)) {printf("Type: Link\n");}
    if(S_ISREG(buf.st_mode)) {printf("Type: File\n");}
    if(S_ISDIR(buf.st_mode)) {printf("Type: Directory\n");}
    if(S_ISCHR(buf.st_mode)) {printf("Type: Char dev\n");}
    if(S_ISBLK(buf.st_mode)) {printf("Type: Block dev\n");}
    if(S_ISFIFO(buf.st_mode)) {printf("Type: FIFO\n");}
    if(S_ISSOCK(buf.st_mode)) {printf("Type: Socket\n");}

    // tiempo
    struct tm *t;
    t = localtime(&buf.st_atime);

    printf("Last access: %d:%d\n", t->tm_hour, t->tm_min);

    return 0;
}
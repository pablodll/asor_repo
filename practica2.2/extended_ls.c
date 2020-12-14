#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[]){
    struct stat st;
    struct dirent *dp;
    int size = 0;

    if(argc <= 1){
        fprintf(stderr, "Missing argument\n");
        return -1;
    }

    if(stat(argv[1], &st) == -1){
        perror("stat error");
    }

    if(S_ISDIR(st.st_mode)){
        DIR *dir = opendir(argv[1]);

        if(dir = NULL){
            perror("opendir error");
        }
        else{
            dp = readdir(dir);
            // while(dp != NULL){

            //     // if(lstat(dp->d_name, &st) == -1){
            //     //     perror("lstat error");
            //     // }
            //     // else{
            //     //     if(S_ISREG(st.st_mode)) { 
            //     //         printf("%s", dp->d_name); 
            //     //         size = size + st.st_size;
            //     //     }
            //     //     else if(S_ISDIR(st.st_mode)) { 
            //     //         printf("%s/", dp->d_name); 
            //     //     }
            //     //     else if(S_ISLNK(st.st_mode)) { 
            //     //         char *b;
            //     //         if(readlink(dp->d_name, b, st.st_size) == -1){
            //     //             perror("readlink error");
            //     //         }
            //     //         printf("%s -> %s", dp->d_name, b); 
            //     //         size = size + st.st_size;
            //     //     }
            //         // else if(S_IXUSR(st.st_mode)){
            //         //     printf("%s*", dp->d_name); 
            //         //     size = size + st.st_size;
            //         // }
            //     }
            // }

            printf("Files size: %d Kb\n", size/1000);
        }

    }
    else{
        fprintf(stderr, "Argument is not a directory\n");
    }

    return 0;
}
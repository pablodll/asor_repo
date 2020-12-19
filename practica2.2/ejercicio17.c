#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){
    struct stat st;
    struct dirent *dp;
    float size = 0;

    if(argc <= 1){
        fprintf(stderr, "Missing argument\n");
        return -1;
    }

    if(stat(argv[1], &st) == -1){
        perror("stat error");
    }

    if(S_ISDIR(st.st_mode)){
        DIR *dir = opendir(argv[1]);

        if(dir == NULL){
            perror("opendir error");
        }
        else{
            while(dp = readdir(dir)) { // != NULL
                char s[100];
                strcpy(s, argv[1]);
                strcat(s, "/");
                strcat(s, dp->d_name);

                if(lstat(s, &st) == -1){
                    perror("lstat error");
                }
                else{
                    if(S_ISDIR(st.st_mode)) { 
                        printf("%s/\n", dp->d_name); 
                    }
                    else if(S_ISREG(st.st_mode)) { 
                        if(st.st_mode & S_IXUSR){
                            printf("%s*\n", dp->d_name); 
                        }
                        else{
                            printf("%s\n", dp->d_name); 
                        }
                        size = size + st.st_size;
                    }
                    else if(S_ISLNK(st.st_mode)) { 
                        char b[50];
                        if(readlink(s, b, 100) == -1){
                            perror("readlink error");
                        }
                        printf("%s -> %s\n", dp->d_name, b); 
                        size = size + st.st_size;
                    }
                }
            }

            printf("Files size: %f Kb\n", size/1000);
        }

    }
    else{
        fprintf(stderr, "Argument is not a directory\n");
    }

    return 0;
}
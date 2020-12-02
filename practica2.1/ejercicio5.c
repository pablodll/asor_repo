#include <stdio.h>
#include <sys/utsname.h>

int main(){
    struct utsname info;
    if(uname(&info) == -1){
        perror("ERROR");
    }
    else{
        printf("System name: %s\n", info.sysname);
        printf("Node name: %s\n", info.nodename);
        printf("Release: %s\n", info.release);
        printf("Version: %s\n", info.version);
        printf("Machine: %s\n", info.machine);
    }

    return 0;
}
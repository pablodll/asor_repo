#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main(){
    
    pid_t pid = getpid();
    pid_t ppid = getppid();
    gid_t gid = getgid();
    pid_t sid = getsid(pid);

    char dir[100];
    if(getcwd(dir, 100) == NULL){
        perror("getcwd error");
    }

    struct rlimit rlim;
    if(getrlimit(RLIMIT_NOFILE, &rlim) == -1){
        perror("getrlimit error");
    }    

    printf("PID: %d, PPID: %d, GID: %d, SID: %d\n", pid, ppid, gid, sid);
    printf("Max open files: %d\n", rlim.rlim_max);
    printf("CWD: %s\n", dir);

    return 0;
}
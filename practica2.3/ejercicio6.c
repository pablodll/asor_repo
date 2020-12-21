#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main(){
    
    pid_t pid = fork();

    if(pid == 0) { // HIJO
        pid_t sid = setsid(); // Nueva sesion

        if(sid == -1){
            perror("setsid error");
        }

        chdir("/tmp"); // Cambiar directorio

        // Mostrar datos proceso
        pid_t pid = getpid();
        pid_t ppid = getppid();
        gid_t gid = getgid();

        char dir[100];
        if(getcwd(dir, 100) == NULL){
            perror("getcwd error");
        }

        sleep(5); // Dormir hijo (demonio) para que padre acabe antes

        printf("CHILD\n");
        printf("PID: %d, PPID: %d, GID: %d, SID: %d\n", pid, ppid, gid, sid);
        printf("CWD: %s\n", dir);
    }
    else if(pid > 0) { // PADRE
        // sleep(5); // Dormir padre para que hijo acabe antes
    }
    else {
        perror("fork error");
        return -1;
    }

    return 0;
}
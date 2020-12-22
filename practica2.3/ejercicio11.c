#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(){

    sigset_t blk_set;

    __sigemptyset(&blk_set);
    __sigaddset(&blk_set, SIGINT);
    __sigaddset(&blk_set, SIGTSTP);

    if(sigprocmask(SIG_BLOCK, &blk_set, NULL) == -1){
        perror("signal block error");
    }

    // const char *s = getenv("SLEEP_SECS");
    sleep(5);

    sigset_t pending;
    if(sigpending(&pending) == -1){
        perror("sig pending error");
    }
    
    if(__sigismember(&pending, SIGINT)){
        printf("\nSIGINT recibida\n");
    }
    if(__sigismember(&pending, SIGTSTP)){
        
        sigset_t stp_set;
        __sigemptyset(&stp_set);
        __sigaddset(&stp_set, SIGTSTP);

        if(sigprocmask(SIG_UNBLOCK, &stp_set, NULL) == -1){
            perror("signal unblock error");
        }

        printf("SIGTSTP unblocked\n");
    }

    return 0;
}
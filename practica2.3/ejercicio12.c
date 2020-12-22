#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int n_sigint = 0, n_sigtstp = 0;

static void sigintHandler(int signal){
    n_sigint = n_sigint + 1;
}

static void sigtstpHandler(int signal){
    n_sigtstp = n_sigtstp + 1;
}

int main(){
    
    struct sigaction sigint_handler;
    struct sigaction sigtstp_handler;

    sigint_handler.sa_handler = sigintHandler;
    sigtstp_handler.sa_handler = sigtstpHandler;

    if(sigaction(SIGINT, &sigint_handler, NULL) == -1){
        perror("sigaction SIGINT error");
    }
    if(sigaction(SIGTSTP, &sigtstp_handler, NULL) == -1){
        perror("sigaction SIGTSTP error");
    }

    while(n_sigint + n_sigtstp < 10){

    }

    printf("\nNum SIGINT: %d, Num SIGTSTP: %d\n", n_sigint, n_sigtstp);

    return 0;
}
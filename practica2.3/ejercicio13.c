#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>

volatile bool del = false;

static void alarmHandler(int signal){
    del = true;
}

int main(int argc, char *argv[]){
    sigset_t set;
    sigset_t pending;
    struct sigaction alarm_handler;

    __sigfillset(&set);
    __sigdelset(&set, SIGALRM);
    __sigdelset(&set, SIGUSR1);

    alarm_handler.sa_handler = alarmHandler;

    if(sigaction(SIGALRM, &alarm_handler, NULL) == -1){
        perror("sigaction SIGALRM error");
    }

    alarm(10);

    sigsuspend(&set);

    if(del){
        char rm[100];
        strcpy(rm, "rm ");
        strcat(rm, argv[0]);
        system(rm);
    }

    return 0;
}
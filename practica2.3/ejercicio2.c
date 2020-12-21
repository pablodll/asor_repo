#include <stdio.h>
#include <sched.h>
#include <unistd.h>

int main(){
    int max, min, policy;
    struct sched_param p;

    policy = sched_getscheduler(0);

    switch (policy)
    {
        case SCHED_OTHER:
            printf("Política: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Política: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Política: SCHED_RR\n");
            break;
    
        case -1:
            perror("getscheduler error");
            break;
    }

    if(sched_getparam(0, &p) == -1) { 
        perror("getparam error"); 
    }
    printf("Prioridad: %d\n", p.__sched_priority);

    max = sched_get_priority_max(policy);
    if(max == -1){
        perror("get max error");
    }
    min = sched_get_priority_min(policy);
    if(min == -1){
        perror("get min error");
    }
    printf("Min: %d, Max: %d\n", min, max);

    return 0;
}